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

char Rdata[16];
int iR = 0;

void dataSR();

void initialize_USART(){
	 /*
	 USART property definition
	 BAUD_PRESCALE ((( F_CPU / ( USART_BAUDRATE * 16UL ))) - 1)
	 */
	unsigned long Speed = ((( F_CPU / ( USART_BAUDRATE * 16UL ))) - 1);
		
	UCSRB = 0b10011000;			// Turn on the transmission and reception circuitry
	UCSRC = 0b10000110;			// Use 8- bit character sizes

	UBRRH = ( Speed >> 8) ; // Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRRL = Speed ; // Load lower 8 - bits of the baud rate value into the low byte of the UBRR register
}
void USART_putc (char Data){
	while (( UCSRA & (1 << UDRE )) == 0) {};  // Do nothing until UDR is ready for more data to be written to it
	UDR = Data;
}
void USART_puts (const char *Data){
	// Cycle through each character individually
	while (*Data){
		USART_putc(*Data++);
	}
}

int main(void) {
	initialize_USART();		
	for(int i = 0; i < 10; i++){
		USART_puts("Hello WORLD!!! \r\n");
	}	
	sei();		
    /* Replace with your application code */
    while (1) {
    }
}

void dataSR(){
	USART_puts(Rdata);
}

ISR(USART_RXC_vect){
	Rdata[iR] = UDR;
	iR++;
	if(Rdata[iR - 1] == '\r'){
		Rdata[iR] = '\0';
		dataSR();
		iR=0;
	}
}
