// Type B
// https://youtu.be/md3sUd1wOGU
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DDR_LED  DDRC     // active HIGH
#define PORT_LED PORTC	
#define DDR_SW	 DDRA	  // active low
#define PORT_SW	 PORTA	
#define PIN_SW	 PINA

void init_port(void);
void init_reset(void);

int main(void)
{
	init_port();
	init_reset(); //[Problem 1]
	
	unsigned char flag[5] = {0,0,0,0,0};
	unsigned char cntSW[5] = {0,0,0,0,0};
	unsigned char pushSW[5] = {0x02,0x04,0x08,0x10,0x20};
	unsigned char onLED[6] = {0x02,0x04,0x08,0x10,0x20,0x40};
	
	while (1)
	{
		unsigned char key = ~(PIN_SW) &	0b00111110;
		_delay_ms(5);  // for debouncing
		
		
		if(key & pushSW[0])  // SW1, [Problem 2]
		{
			PORT_LED |= (onLED[0] | onLED[1] | onLED[2]);
			flag[0] = 1;
		}
		else if(flag[0]==1) 
		{
			PORT_LED &= ~(onLED[0] | onLED[1] | onLED[2]);
			flag[0] = 0;
		}
		
		if(key & pushSW[1]) // SW2, [Problem 3]
		{
			PORT_LED |= (onLED[3] | onLED[4] | onLED[5]);
			flag[1] = 1;
		}
		else if(flag[1]==1)
		{
			PORT_LED &= ~(onLED[3] | onLED[4] | onLED[5]);
			flag[1] = 0;
		}
		
		if(key & pushSW[2]) // SW3, [Problem 4]
		{
			cntSW[3] = 0;
			if(flag[2] == 0)
			{
				if(cntSW[2] < 6) PORT_LED = (0x02<<cntSW[2]);
				else			 PORT_LED = (0x02<<(10-cntSW[2]));
	
				cntSW[2]++;
				if(cntSW[2] == 10)	 cntSW[2] = 0;
	
				flag[2] = 1;
			}
		}
		else flag[2] = 0;
		
		if(key & pushSW[3]) // SW4, [Problem 5]
		{
			cntSW[2] = 0;

			if(flag[3] == 0)
			{
				unsigned char tempLED = 0x02;
				if(cntSW[3] < 6) 
				{
					for (int i=0 ; i<=cntSW[3] ; i++) tempLED |= 0x02<<i;
					PORT_LED = tempLED ;
				}
				else
				{
					for (int i=0 ; i<=(cntSW[3]-6) ; i++) tempLED = 0b00111110>>i;
					PORT_LED = tempLED;
				}
				
				cntSW[3]++;
				if(cntSW[3] == 10)	 cntSW[3] = 0;
				
				flag[3] = 1;	
			}			
		}
		else flag[3] = 0;
		
		if(key & pushSW[4]) // SW5, [Problem 6]
		{
			if(flag[4] == 0)
			{
				init_reset();
				
				for (int i=0 ; i<5 ; i++) cntSW[i] = 0;
				
				flag[4] = 1;
			}
		}
		else flag[4] = 0;

	}
}

void init_port(void)
{
	DDR_LED  |= 0b01111110; // PC1 ~ PC6, OUTPUT, PC0,7 - don't care
	PORT_LED &= 0b10000001; // LED Off
	DDR_SW   &= 0b11000001; // PA1 ~ PA5, INPUT, PA0,6,7 - don't care
	PORT_SW  |= 0b00111110; // internal Pull-up resistor
}

void init_reset(void)
{
	for(int i=0 ; i<3 ; i++)
	{
		PORT_LED = 0b01111110;	// LED on
		_delay_ms(300);
		PORT_LED = 0b00000000;	// LED off
		_delay_ms(300);
	}
	PORT_LED = 0b00000010;
}

