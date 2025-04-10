#include<LPC17xx.h>
int main(void){
	unsigned int j,i;
	unsigned long c=1;

	LPC_PINCON->PINSEL0&=0xFF0000FF;
	SystemInit();
	SystemCoreClockUpdate();
	//LPC_PINCON->PINSEL0 &=0xFF0000FF;
	LPC_GPIO0->FIODIR |=0x00000FF0;
	//LPC_PINCON->PINSEL4&=0xFFFFFFCC;
	//LPC_GPIO2->FIODIR&=0xFFFFFFFE;
	while(1){
		if(!(LPC_GPIO2->FIOPIN & 1<<12)){
			for(j=0;j<8;j++){
				LPC_GPIO0->FIOPIN=c<<4;
				for(i=0;i<1000000;i++);
				c=c<<1;}}
		c=1;
			}
		}