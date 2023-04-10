#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int ledVal = 0;

ISR(INT0_vect)
{
	ledVal = 1;
}

ISR(INT1_vect)
{
	ledVal = 0;
}

int main(void)
{
  DDRA = 0x01;
	PORTA = 0x01; // LED 초기화
	DDRD = 0x00;
	PORTD = 0x03; // pull-up
	
	// INT0, INT1 활성화
	EIMSK |= (1<<INT0) | (1<<INT1);  // EIMSK |= 0x03;
	// INT0은 상승에지, INT1은 하강에지
	EICRA |= (1<<ISC00) | (1<<ISC01) | (1<<ISC11);  // EICRA |= 0x0b; // ob00001011
	//인터럽트 활성화
	sei(); //SREG |= 0x80 // <-> cli();
	
	
	while (1) 
  {
		if(ledVal) PORTA = 0x00;
		else PORTA = 0x01;
  }
}

