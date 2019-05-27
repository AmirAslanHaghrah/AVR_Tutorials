#define F_CPU 8000000
#define USART_BAUDRATE 9600

#define BIT(x) (0x01 << (x))
#define bit_get(p,m) ((p) & (m))

#include <io.h>

char Rdata[4];
int iR = 0;

void dataSR();

void initialize_USART() {
    unsigned long Speed = (((F_CPU / (USART_BAUDRATE * 16UL))) - 1);
        
    UCSRB = 0b10011000;
    UCSRC = 0b10000110;

    UBRRH = (Speed >> 8);
    UBRRL = Speed ;
}

void USART_putc (char Data) {
    while ((UCSRA & (1 << UDRE)) == 0) {};
    UDR = Data;
}

void USART_puts (const char *Data) {
    while (*Data){
        USART_putc(*Data++);
    }
}

void main() {
    initialize_USART(); 
    
    DDRA = 0xff;
    DDRB = 0xff;
           
    #asm("sei");      
    while (1) {}
}

void dataSR() {
    USART_puts(Rdata);
}

interrupt [USART_RXC] void usart_ex_isr(void) {
    Rdata[iR] = UDR; 
    iR++; 
    
    if(Rdata[iR - 1] == '\r'){
        Rdata[iR] = '\0';    
        if (Rdata[0] == 'a') {
            switch(Rdata[1]) {
                case '1':     
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00000001;
                    } else if (Rdata[2] == 'c') {
                        PORTA &= ~BIT(0);
                    }
                    break;
                case '2':  
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00000010;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(1)));
                    }
                    break;
                case '3': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00000100;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(2)));
                    }
                    break;
                case '4': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00001000;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(3)));
                    }
                    break;
                case '5': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00010000;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(4)));
                    }
                    break;
                case '6': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b00100000;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(5)));
                    }
                    break;
                case '7': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b01000000;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(6)));
                    }
                    break;
                case '8': 
                    if (Rdata[2] == 'o') {
                        PORTA |= 0b10000000;
                    } else if (Rdata[2] == 'c') {
                        ((PORTA) &= ~(BIT(7)));
                    }
                    break;
            }
        } else if (Rdata[0] == 'b') {
            switch(Rdata[1]) {
                case '1': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00000001;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '2': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00000010;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '3': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00000100;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '4': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00001000;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '5': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00010000;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '6': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b00100001;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '7': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b01000000;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
                case '8': 
                    if (Rdata[2] == 'o') {
                        PORTB = 0b10000000;
                    } else if (Rdata[2] == 'c') {
                        PORTB = 0b00000000;
                    }
                    break;
            }
        }
        
        dataSR();
        iR=0;
    }
}
