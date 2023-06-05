#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main()
{//Timer/Counter 0
  DDRB = 0x10; // for output OC0
  //1. TCCR0 : Phase correct PWM Mode, COM01:0(10,11), CS02:0(clk/64)
  TCCR0 |= (0<<WGM01) | (1<<WGM00) | (1<<COM01) | (0<<COM00) | (1<<CS02) | (0<<CS01) | (0<<CS00);
  //2. TIMSK0
  TIMSK |= (0<<OCIE0) | (0<<TOIE0);
  //3. SREG
  sei();

  // Top Value
  OCR0 = 50;

  while (1) 
  {
  // 메인 프로그램 실행
  }
  return 0;
}

