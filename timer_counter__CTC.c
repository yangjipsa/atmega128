#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect) {

}

int main() 
{  //Timer/Counter 0
   DDRB = 0x10; // for output OC0
   //1. TCCR0 : CTC Mode, COM01:0(01,10,11), CS02:0(clk/64)
   TCCR0 |= (1<<WGM01) | (0<<WGM00) | (0<<COM01) | (1<<COM00) | (1<<CS02) | (0<<CS01) | (0<<CS00);
   //2. TIMSK0
   TIMSK |= (1<<OCIE0) | (0<<TOIE0);
   //3. SREG 
   sei();

   // Top Value
   OCR0 = 127;

   while (1) 
   { // 메인 프로그램 실행
   }
   return 0;
}
