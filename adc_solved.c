#include<LPC17xx.h> 
#include<stdio.h> 
#include"LCD_q1.c" 
#define Ref_Vtg 3.300 	//Reference voltage (3.3V for the ADC)
#define Full_Scale 0xFFF	//Full scale ( maximum possible ADC value) for a 12-bit ADC (4095 in decimal)

int main(void) {
	unsigned long adc_temp; 	//hold the ADC conversion result
	unsigned int i; 
	float in_vtg; 	//stores the calculated input voltage
	unsigned char vtg[7], dval[7]; 	//hold strings for displaying voltage and ADC value
	
	unsigned char Msg3[11] = {"ANALOG IP:"}; 
	unsigned char Msg4[12] = {"ADC OUTPUT:"}; 
	SystemInit(); 
	SystemCoreClockUpdate();
	
	LPC_SC->PCONP |= (1<<15);    //Power for GPIO block 
	lcd_init(); 
	LPC_PINCON->PINSEL3 |= 0xC0000000;  //P1.31 as AD0.5 
	LPC_SC->PCONP |= (1<<12);   //enable the peripheral ADC 
  
	SystemCoreClockUpdate(); 
  
	lcd_comdata(0x80, 0); 
	delay_lcd(800); 
	lcd_puts(&Msg3[0]); 

	lcd_comdata(0xC0, 0); 
	delay_lcd(800); 
	lcd_puts(&Msg4[0]); 

	while(1){ 
		LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24); //0x01200001;   
		//ADC0.5, start conversion and operational  
		
		while(!(LPC_ADC->ADDR5 & 0x80000000)); 
					//wait till 'done' bit is 1, indicates conversion complete 
		
		adc_temp = LPC_ADC->ADDR5; 
		adc_temp >>= 4; 
		adc_temp &= 0x00000FFF;    //12 bit ADC 
		in_vtg = (((float)adc_temp * (float)Ref_Vtg))/((float)Full_Scale); 
		
		//calculating input analog voltage 
		sprintf(vtg, "%3.2fV", in_vtg);  
		//convert the readings into string to display on LCD 
		sprintf(dval, "%x", adc_temp); 
		
		for(i=0; i<2000; i++); 

		lcd_comdata(0x8B, 0); 
		delay_lcd(800); 
		lcd_puts(&vtg[0]); 

		lcd_comdata(0xCC, 0); 
		delay_lcd(800); 
		lcd_puts(&dval[0]);
		
		for(i=0;i<200000;i++); 

		for(i=0;i<7;i++) 
			vtg[i] = dval[i] = 0x00; 
			
		adc_temp = 0; 
		in_vtg = 0; 
	} 
}