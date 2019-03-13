/*
 * interrupt_test.cpp
 *
 * Created: 3/10/2019 3:01:36 PM
 * Author : amiraslan haghrah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	MCUCR = 0b00000001;
	GIFR = 0b01000000;
	GICR = 0b01000000;
	
	sei();
	    
    while (1) 
    {
		PORTB = ~PORTB;	
		for(long i = 0; i < 10000; i++){}
    }
}

ISR(INT0_vect){
	PORTA = ~PORTA;	
}
