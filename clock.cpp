/*
 * timerTest.cpp
 *
 * Created: 12/2/2018 2:29:50 PM
 * Author : AmirAslan Haghrah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TCCR0 = 0b00000010;
	TCNT0 = 0;
	OCR0 = 124;
	TIMSK = 0b00000011;	
	
	sei();
    while (1) {}
}

long millisecond = 0;
int second = 0;
int minute = 0;
int hour = 0;
 
 ISR(TIMER0_OVF_vect){
	 PORTB = ~PORTB;
 }
 
ISR(TIMER0_COMP_vect){
	PORTA = ~PORTA;
	if (millisecond < 1000){
		millisecond++;
	}else{
		millisecond = 0;
		if(second < 60){
			second ++;	
		}else{
			second = 0;
			if (minute < 60){
				minute++;
			}else{
				minute = 0;
				if (hour < 24){
					hour++;
				}else{
					hour = 0;
				}
			}
		}
	}
}

