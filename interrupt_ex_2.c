#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int num = 0;
int n = 10;		// 진법

ISR(INT0_vect)
{
	cli();
	num++;
	if(num>9999) num=0;
	sei();
}

ISR(INT1_vect)
{
	cli();
	num--;
	if(num<0) num = 9999;
	sei();
}

void fnd_disp(unsigned char num);
void dig_disp(unsigned char digit, unsigned char num);

int main(void)
{
	DDRA = 0xff; // fnd, A port Output
	PORTA = 0xff; // display to fnd, nothing
	DDRC = 0x0f; // fnd digit, C port output
	PORTC = 0x0f; // no select any digit
	DDRD = 0x00; // switch, D port, Input
	PORTD = 0x03; // internal pull-up
	
	// INT0, INT1 활성화
	EIMSK |= (1<<INT0) | (1<<INT1);  // EIMSK |= 0x03;
	// INT0, INT1 상승에지
	EICRA |= (1<<ISC00) | (1<<ISC01) | (1<<ISC10)| (1<<ISC11);  // EICRA |= 0x0b; // ob00001111
	//인터럽트 활성화
	sei(); //SREG |= 0x80 // <-> cli();	

	while (1)
	{
		int temp = num;
		unsigned char col[4] = {0,}; // 각 자리의 숫자를 저장할 배열
		int i=0;
		
		while(temp)
		{
			if(n!=0)
			{
				col[i++] = temp % n;
				temp = temp/n;
			}
		}
		
		for (i=0 ; i<4 ; i++)
		{
			dig_disp(i, col[i]);
			_delay_ms(5);
		}
	}
}


void fnd_disp(unsigned char num)
{
	char fnd[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E, 0xFF}; // 0~9, a~f and nothing.
	PORTA = fnd[num];
}

void dig_disp(unsigned char digit, unsigned char num)
{
	PORTC= ~(1<<digit);
	fnd_disp(num);
}
