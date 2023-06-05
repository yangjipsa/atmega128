#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int cnt0 = 0;
volatile int ledVal = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 256 - 200;
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
	sei();	//set Interrupt
	//Normal Mode(OC0 Disconnected), pre-scaler : 1/8
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (1<<CS01) | (0<<CS00);
	TIMSK = (1<<TOIE0); // Timer/Counter overflow Interrupt Enable
	TCNT0 = 256-200;
	
    while (1) 
    {
		if(ledVal) PORTA = 0x00; // led on
		else PORTA = 0x01; // led off
    }
}
