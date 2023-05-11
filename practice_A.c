// Type A
// https://youtu.be/md3sUd1wOGU

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DDR_LED  DDRA     // active low
#define PORT_LED PORTA
#define DDR_SW	 DDRC	  // active low
#define PORT_SW	 PORTC
#define PIN_SW	 PINC

void init_port(void);
void init_reset(void);

int main(void)
{
	init_port();
	init_reset(); //[Problem 1]
	
	unsigned char flag[4] = {0,0,0,0};
	unsigned char cntSW[4] = {0,0,0,0};
	
    while (1) 
    {
		unsigned char key = ~(PIN_SW) &	0x0f;
		_delay_ms(5);  // for debouncing
		
		if(key == 0x01) // sw1, [Problem 2]
		{
			if(flag[0] == 0)
			{
				PORT_LED = 0xEA;
				_delay_ms(500);
				for(int i=0 ; i<9 ; i++)
				{
					PORT_LED ^= 0xFF;
					_delay_ms(500);
				}
				PORT_LED = 0xFE;
				
				flag[0] = 1;
			}
		}
		else flag[0] = 0;
		
		if(key == 0x02) // sw2, [Problem 3]
		{
			
			cntSW[2] = 0;
			
			if(flag[1] == 0)
			{
				if(cntSW[1] < 6) PORT_LED = ~(0x01<<cntSW[1]);
				else			 PORT_LED = ~(0x01<<(10-cntSW[1]));
				
				cntSW[1]++;				
				if(cntSW[1] == 10)	 cntSW[1] = 0;
								
				flag[1] = 1;
			}
		}
		else flag[1] = 0;
		
		if(key == 0x04) //  sw3, [Problem 4]
		{
			cntSW[1] = 0;
			if(flag[2] == 0)
			{
				if(cntSW[2] < 6) PORT_LED = ~(0x01)<<cntSW[2];
				else			 PORT_LED = ~(0x01)<<(10-cntSW[2]);
				
				cntSW[2]++;
				if(cntSW[2] == 10)	 cntSW[2] = 0;
				
				flag[2] = 1;
			}
		}
		else flag[2] = 0;
		
		if(key == 0x08) //  sw4, [Problem 5]
		{
			if(flag[3] == 0)
			{
				init_reset(); 
					
				for (int i=0 ; i<4 ; i++) cntSW[i] = 0;

				flag[3] = 1;
			}
		}
		else flag[3] = 0;
		
    }
}

void init_port(void)
{
	DDR_LED  |= 0x3F; // PA0 ~ PA5, OUTPUT, PA6,7 - don't care
	PORT_LED |= 0x3F; // LED Off
	DDR_SW   &= 0xF0; // PC0 ~ PC3, INPUT, PC4~7 - don't care
	PORT_SW  |= 0x0F; // internal Pull-up resistor  	
}

void init_reset(void)
{
	for(int i=0 ; i<3 ; i++)
	{
		PORT_LED = 0xC0;	// LED on
		_delay_ms(300);
		PORT_LED = 0xFF;	// LED off
		_delay_ms(300);		
	}
	PORT_LED = 0xFE; 
}
