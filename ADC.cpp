/*
 * DataTranmision.cpp
 *
 * Created: 12/16/2018 2:28:36 PM
 * Author : AmirAslan Haghrah
 */ 
#define F_CPU 8000000
#define USART_BAUDRATE 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>


void Init_USART(){
	 /*
	 USART property definition
	 BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL ))) - 1)
	 */
	unsigned long Speed = ((( F_CPU / ( USART_BAUDRATE * 16UL ))) - 1);
		
	UCSRB = 0b10011000;			// Turn on the transmission and reception circuitry
	UCSRC = 0b10000110;			// Use 8- bit character sizes

	UBRRH = Speed >> 8;			// Load upper 8 - bits of the baud rate value into the high byte of the UBRR register
	UBRRL = Speed;				// Load lower 8 - bits of the baud rate value into the low byte of the UBRR register
}
void putChar (char Data){
	while (( UCSRA & 0b00100000) == 0) {};  // Do nothing until UDR is ready for more data to be written to it
	UDR = Data;
}
void putString (const char *Data){
	// Cycle through each character individually
	while (*Data){
		putChar(*Data++);
	}
}
void putInteger (int n){
	char data[16];
	itoa(n, data, 10);	
	putString(data);
}
void Init_ADC(){
	ADMUX = 0b01000000;		// For Aref = AVcc;
	ADCSRA = 0b10000000;	// Prescaler div factor =128
}
uint16_t readADC(){
	//Start Single conversion
	ADCSRA |= 0b01000000;

	//Wait for conversion to complete
	while(!(ADCSRA & 0b00010000)){};
			
	return(ADC);
}
void Init_Timer0(){
	TCNT0 = 0x00;
	OCR0 = 200;	
	TIMSK = 0b00000010;
	TIFR = 0x00;	
	TCCR0 = 0b00001101;
}

int main(void) {
	Init_USART();
	Init_ADC();
	Init_Timer0();
		
	
	putString("Start\r\n");
	
	
	sei();		
    /* Replace with your application code */
    while (1) {}
}

ISR(TIMER0_COMP_vect){		 
	putInteger(readADC()* 5.0 / 1024.0 * 100.0);
	putString("\r\n");
}
