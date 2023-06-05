#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int cnt0 = 0;
volatile int ledVal = 0;

ISR(TIMER0_COMP_vect)
{
	cnt0++;
	if(cnt0 == 10000)
	{
		ledVal = !ledVal;
		cnt0 = 0;
	}
}


int main(void)
{
	DDRA = 0x01; // for LED, Output
	/*3*/sei();	//set Interrupt
	//CTC Mode(10), OC Toggle Mode, pre-scaler : 1/8
	/*1*/TCCR0 = (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00) | (0<<CS02) | (1<<CS01) | (0<<CS00);
	/*2*/TIMSK = (1<<OCIE0); // Timer/Counter Compare Match Interrupt Enable
	OCR0 = 200;
	//TCNT0 = 256-200;
	
	while (1)
	{
		if(ledVal) PORTA = 0x00; // led on
		else PORTA = 0x01; // led off
	}
}

