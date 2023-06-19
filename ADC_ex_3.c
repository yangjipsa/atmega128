#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x10; // for output OC0  
	DDRF = 0x00; // for ADC (input)
	
	// for ADC
	//1. AVCC , ADC0, 
	/*1*/ADMUX = (0<<REFS1) | (1<<REFS0) | (0<<MUX4) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0);
	//2. ADC enable, Start conversion, free running, 1/8 prescaler
	/*2*/ADCSRA = (1<<ADEN) | (1<<ADSC)  | (1<<ADFR) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) |(1<<ADPS0);
	
	// for Timer/Counter
	//1. TCCR0 : fastPWM Mode, COM01:0(10,11), CS02:0(clk/64)
	TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (0<<COM00) | (1<<CS02) | (0<<CS01) | (0<<CS00);
	//2. TIMSK0
	TIMSK |= (0<<OCIE0) | (0<<TOIE0);
	
	//main code
	while (1)
	{
		int adcVal = (ADCH<<8) + ADCL;
		OCR0 = adcVal / 4; // range : 0 ~ 255
	}
}
