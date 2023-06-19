#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

char fnd[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E}; //for common-anode
int n = 10;     // 나누는 숫자(진법)
	
int main(void)
{
	DDRA = 0xff;  
	DDRC = 0x0f;
	DDRF = 0x00; // for ADC (input)
	
	//1. AVCC , ADC0, 
	/*1*/ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<MUX4) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	//2. ADC enable, Start conversion, free running, 1/8 prescaler
	/*2*/ADCSRA = (1<<ADEN) | (1<<ADSC)  | (1<<ADFR) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) |(1<<ADPS0);
	//Variables
	
	//main code
	while (1)
	{
		unsigned char col[4] = {0,}; 
		int i=0;
		
		int adcVal = (ADCH<<8) + ADCL;
		int temp = adcVal;	
		
		while(temp) // 각 자릿수를 배열 col에 저장
		{
			if(n!=0)
			{
				col[i] = temp % n;
				temp = temp / n;
				i++;
			}
		}
		
		for(i=0; i<4; i++) // 배열 col에 저장된 숫자를 각 자리에 맞춰 출력
		{
			PORTC = (1<<i);
			PORTA = ~fnd[col[i]]; // fnd배열을 반전해서 출력
			_delay_ms(5);
		}
	}
}
