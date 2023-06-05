#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned int cnt0 = 0;
unsigned char sec = 0;
unsigned char min = 0;
unsigned char hour = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 256 - 200;
	cnt0++;
	if(cnt0 == 10000) 
	{
		sec++;
		if(sec>60)
		{
			sec=0;
			min++;
			if(min>60)
			{
				min=0;
				hour++;
				if(hour>24) hour=0;				
			}
		}
		cnt0=0;
	}
}


int main(void)
{
	DDRA  = 0xff;  // fnd port, active-high, common-cathode
	PORTA = 0x00;  // fnd off
	DDRC  |= 0x0f; // fnd digit port, active-high, npn TR
	PORTC &= 0xf0; // no fnd select.
	
	sei();	//set Interrupt
	//Normal Mode(OC0 Disconnected), pre-scaler : 1/8
	TCCR0 = (0<<WGM01) | (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<CS02) | (1<<CS01) | (0<<CS00);
	TIMSK = (1<<TOIE0); // Timer/Counter overflow Interrupt Enable
	TCNT0 = 256-200;
	
	char fnd[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E}; //for common-anode
	int n = 10;     // 나누는 숫자(진법)
	
	while (1)
	{
		unsigned char col[4] = {0,};  //fnd에 출력할 자릿수 저장 배열
		int i=0;
		int num2 = min + hour*100;
		while(num2) // 각 자릿수를 배열 col에 저장
		{
			if(n!=0)
			{
				col[i] = num2 % n;
				num2 = num2 / n;
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

