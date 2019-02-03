/*
 * extInterrupts.cpp
 *
 * Created: 10/27/2018 9:29:38 PM
 * Author : AmirAslan Haghrah
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)	{	
	DDRA = 0xFF;		
	MCUCR = 0b00000011;
	GICR = 0b01000000;
	
	sei();	
    /* Replace with your application code */
    while (1) {}
}

ISR(INT0_vect){
	PORTA = ~PORTA;
}

