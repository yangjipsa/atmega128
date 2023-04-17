#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// PORT Initialize
	DDRA  = 0xff;  // fnd port, active-high, common-cathode
	PORTA = 0x00;  // fnd off
	DDRC  |= 0x0f; // fnd digit port, active-high, npn TR
	PORTA &= 0xf0; // no fnd select.
	
	//Variables
	char fnd[16] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xA7, 0xA1, 0x86, 0x8E}; //for common-anode
	int num = 2580; // 출력하려는 숫자
	int n = 10;     // 나누는 숫자(진법)
	unsigned char col[4] = {0,};  //fnd에 출력할 자릿수 저장 배열
	int i=0;
	
	while(num) // 각 자릿수를 배열 col에 저장
	{
		if(n!=0)
		{
			col[i] = num % n;
			num = num / n;
			i++;
		}
	}
	
	//main code
	while (1) 
    {
		for(i=0; i<4; i++) // 배열 col에 저장된 숫자를 각 자리에 맞춰 출력
		{
			PORTC = (1<<i);
			PORTA = ~fnd[col[i]]; // fnd배열을 반전해서 출력
			_delay_ms(5);
		}
    }
}
