#include <LPC17xx.h>
void initPWM(void);
void updatePulseWidth(unsigned int pulseWidth);
void delayMS(unsigned int milliseconds);
int main(void)
{
int pulseWidths[] = {0, 3000, 6000, 9000, 12000, 15000, 18000, 21000, 24000, 
27000}; 
const int numPulseWidths = 10;
int count=1;
int dir=0;
initPWM(); 
while(1)
{
updatePulseWidth(pulseWidths[count]); 
delayMS(1000000); //put delay 10000 for the minimum fast 100000 for delay upto 500000
	
	if(count == (numPulseWidths-1) || count == 0)
{
dir = !dir;
}
if(dir) count--;
else count++;
}
}
void initPWM(void)
{
LPC_PINCON->PINSEL3 |= 0x8000;  
LPC_PWM1->PCR = 0x1000;
LPC_PWM1->PR = 0; 
LPC_PWM1->MR0 = 30000; //period=10ms if pclk=cclk/4
LPC_PWM1->MCR = (1<<1); //Reset PWM TC on PWM1MR0 match
LPC_PWM1->LER = 0xff; //update values in MR0 and MR1
 LPC_PWM1->TCR = 0x00000002; //RESET COUNTER TC and PC
LPC_PWM1->TCR = 0x00000009; //enable TC and PC
}
void updatePulseWidth(unsigned int pulseWidth)
{
LPC_PWM1->MR4 = pulseWidth; //Update MR4 with new value
LPC_PWM1->LER = 0xff; //Load the MR4 new value at start of next cycle
}
void delayMS(unsigned int milliseconds) //Using Timer0
{
LPC_TIM0->CTCR = 0x0; //Timer mode
LPC_TIM0->PR = 2; //Increment TC at every 3 pclk
LPC_TIM0->TCR = 0x02; //Reset Timer
LPC_TIM0->TCR = 0x01; //Enable timer
while(LPC_TIM0->TC < milliseconds); 
LPC_TIM0->TCR = 0x00; //Disable timer
}
	