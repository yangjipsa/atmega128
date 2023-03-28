#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DDR DDRA
#define FND_OUT PORTA

void fnd_init(void);
void fnd_disp(unsigned char num);

int main(void)
{
	fnd_init();
	
    while (1) 
    {
		for (int i=0 ; i<10 ; i++)
		{
			fnd_disp(i);
			_delay_ms(1000);
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
	char fnd[11] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF}; // 0~9 and nothing.
	FND_OUT = fnd[num];
}
