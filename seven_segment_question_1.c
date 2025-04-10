#include<LPC17xx.h>

unsigned int dig_count = 0x00;
unsigned char tohex[10] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
unsigned int dig_value[4] = {4,3,2,1};
unsigned int dig_selec[4] = {0<<23, 1<<23, 2<<23, 3<<23};
unsigned int i=0, j=0;

void delay(void);
void display(void);

int main() {
    LPC_GPIO0->FIODIR|=0XFF<<4; //P0.4 to P0.11 as output
    LPC_GPIO1->FIODIR|=0XF<<23; //P1.23 to P1.26 as output

    while(1) {
        delay();
        display();
        dig_count++;
        if(dig_count == 0x04) {
            dig_count = 0x00;
        }
    }
}

void delay(void) {
    for(j=0; j<50000; j++);
}

void display(void) {
    LPC_GPIO1->FIOPIN=dig_selec[dig_count];
    LPC_GPIO0->FIOPIN=tohex[dig_value[dig_count]]<<4;
}