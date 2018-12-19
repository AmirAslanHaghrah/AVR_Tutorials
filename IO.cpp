/*
 * IO_Ports.cpp
 *
 * Created: 5/6/2017 7:12:04 PM
 * Author : AmirAslan Haghrah
 */ 
#define F_CPU 1000000

#include <avr/io.h>

int main(void){
	
	DDRA = 0xFF;		//PORTA as OUTPUT
	DDRD = 0x00;		//PORTD as INPUT
	

    /* Replace with your application code */
    while (1) 
    {
		if ( PIND == 0b00000101){
			PORTA = 0x01;	
		}else{
			PORTA = 0x00;	
		}
    }
}

