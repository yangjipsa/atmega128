#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DDR DDRA
#define FND_OUT PORTA
#define DIG_DDR DDRC
#define DIG_OUT PORTC

void fnd_init(void);
void fnd_disp(unsigned char num);
void dig_init(void);
void dig_disp(unsigned char digit, unsigned char num);

int main(void)
{
	fnd_init();
	dig_init();
	
	int num = 1234; // 원하는 숫자
	int n = 10;		// 진법
	unsigned char col[4] = {0,}; // 각 자리의 숫자를 저장할 배열
	int i=0;
		
	while(num)
	{
		if(n!=0)
		{
			col[i++] = num % n;
			num = num/n;
		}
	}
	
    while (1) 
    {
		for (i=0 ; i<4 ; i++)
		{
			dig_disp(i, col[i]);
			_delay_ms(5);
		}
    }
}

void fnd_init(void)
{
	FND_DDR = 0xFF; // set OUTPUT
	fnd_disp(10);
}

void fnd_disp(unsigned char num)
{
	char fnd[17] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E, 0xFF}; // 0~9, a~f and nothing.
	FND_OUT = fnd[num];
}

void dig_init(void)
{
	DIG_DDR = 0x0F;
}

void dig_disp(unsigned char digit, unsigned char num)
{
	DIG_OUT= ~(1<<digit);
	fnd_disp(num);	
}
