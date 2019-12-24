/*
 * HeartBeat.cpp
 *
 * Created: 12/22/2019 9:59:40 AM
 * Author : Amiraslan Haghrah
 */ 

#define F_CPU 8000000
#define Baud 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

void Init_USART() {
	 /*
	 USART property definition
	 BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL ))) - 1)
	 */
	unsigned long Speed = ((( F_CPU / ( Baud * 16UL ))) - 1);
		
	UCSRB = 0b10011000;			// Turn on the transmission and reception circuitry
	UCSRC = 0b10000110;			// Use 8- bit character sizes

	UBRRH = Speed >> 8;			// Load upper 8 - bits of the baud rate value into the high byte of the UBRR register
	UBRRL = Speed;				// Load lower 8 - bits of the baud rate value into the low byte of the UBRR register
}
void putChar (char data ){
	while (( UCSRA & 0b00100000) == 0) {};  // Do nothing until UDR is ready for more data to be written to it
	UDR = data;
}
void putString (const char *data) {
	// Cycle through each character individually
	while (*data){
		putChar(*data++);
	}
}
void putInteger (int n) {
	char data[16];
	itoa(n, data, 10);	
	putString(data);
}

void Init_Timer0() {
	TCNT0 = 0x00;
	OCR0 = 77;
	TIMSK = 0b00000010;
	TIFR = 0b00000010;
	TCCR0 = 0b00001101;
}

void Init_ADC() {
	ADMUX = 0b01000000;		// For Aref = AVcc;
	ADCSRA = 0b10000000;	// Prescaler div factor =128
}
uint16_t readADC() {
	//Start Single conversion
	ADCSRA |= 0b01000000;
	
	//Wait for conversion to complete
	while(!(ADCSRA & 0b00010000)){};
	
	return(ADC);
}

int main(void)
{
	Init_USART();
	Init_ADC();
	Init_Timer0();
	
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		//putString("hello\r\n");
    }
}

ISR(TIMER0_COMP_vect){	
	//putString("hello\r\n");
	putInteger(readADC());
	putString("\r\n");	
}
