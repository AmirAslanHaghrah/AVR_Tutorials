#include <io.h>

void Initialize();
void PutChar(char data);
void PutString(char* data);

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void){
    if(UDR == '1'){
        PORTC = 0b00000001;   
    }
    if(UDR == '2'){
        PORTC = 0b00000010;   
    }
    if(UDR == '3'){
        PORTC = 0b00000100;   
    }
    if(UDR == '4'){
        PORTC = 0b00001000;   
    }    
}

void Initialize(){
    UCSRB = 0b10011000;
    UCSRC = 0b10000110;
    
    UBRRH = 51 >> 8;
    UBRRL = 51;
}

void PutChar(char data){
    while((UCSRA & 0b00100000) == 0){}
    UDR = data;
}

void PutString(char* data){
    while(*data){
        PutChar(*data++);
    }
}

void main(){
    DDRC = 0xFF;
    
    Initialize();    
    PutString("Please Enter Number:\r\n");
    
    #asm("sei");    
    
    while(1){        
    }
}
