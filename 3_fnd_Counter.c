#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DDR DDRA
#define FND_OUT PORTA
#define DIG_DDR DDRC // 0,1,2,3
#define DIG_OUT PORTC
#define SW_DDR  DDRB // 0,1
#define SW_IN	PINB

void fnd_init(void);
void fnd_disp(unsigned char num);
void dig_init(void);
void dig_disp(unsigned char digit, unsigned char num);
void dig4_disp(int NUM, int N);
void sw_init(void);
unsigned char sw_read(void);

int main(void)
{
	fnd_init();
	dig_init();
	sw_init();
	
	int num =0; // 원하는 숫자
	int n = 10;		// 진법
	unsigned char sw_val = 0;
	unsigned char flag1 = 0, flag2 = 0;
	

	
	while (1)
	{
		sw_val = sw_read();
		
		if(sw_val & 0x01) 
		{
			if(flag1 == 0)
			{
				num++;
				if (num > 9999) num = 9999;
				flag1 = 1;
			}
		}
		else flag1 = 0;
		
		if(sw_val & 0x02)
		{
			if(flag2 == 0)
			{
				num--;
				if(num < 0) num = 0;	
				flag2 = 1;
			}
		}
		else flag2 = 0;
		
		dig4_disp(num,n);
	}
}

void fnd_init(void)
{
	FND_DDR = 0xFF; // set OUTPUT
	fnd_disp(17);
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

void dig4_disp(int NUM, int N)
{
			
	int temp = NUM;
	unsigned char col[4] = {0,}; // 각 자리의 숫자를 저장할 배열
	int i=0;
		
	while(temp)
	{
		if(N!=0)
		{
			col[i++] = temp % N;
			temp = temp/N;
		}
	}
	
	for (i=0 ; i<4 ; i++)
	{
		dig_disp(i, col[i]);
		_delay_ms(5);
	}
}

void sw_init(void)
{
	SW_DDR = 0x00;
	PORTB = 0xff;
}

unsigned char sw_read(void)
{
	return ~(SW_IN) & 0x03;
}
