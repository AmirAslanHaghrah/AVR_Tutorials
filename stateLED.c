#include <io.h>

void update();

   int n = 0;
   int sec = 0;  
   
   int st = 0;
   int p = 0;
   
// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void){
    if ( p == 0){
        if (n < 333){
            n++;
        }else{     
            //sec++;
            p = 1;
            OCR0 = 62;
            n = 0;
        }        
    }else if (p == 1){
        sec++;
        OCR0 = 187;
        p = 0;
        update();
    } 
}

void update(){
    if(st == 0 && sec ==2){
        sec = 0;
        st = 1;
        PORTC = 0x02; 
    }   
    else if(st == 1 && sec ==3){
        sec = 0;
        st = 2;
        PORTC = 0x04; 
    } 
    else if(st == 2 && sec ==4){
        sec = 0;
        st = 3;
        PORTC = 0x08; 
    }  
    else if(st == 3 && sec ==5){
        sec = 0;
        st = 4;
        PORTC = 0x04; 
    }    
    else if(st == 4 && sec ==4){
        sec = 0;
        st = 5;
        PORTC = 0x02; 
    }    
    else if(st == 5 && sec ==3){
        sec = 0;
        st = 0;
        PORTC = 0x01; 
    }  
}


void main(){
    DDRC = 0xFF;    // PORTC all pins as output.
    PORTC = 0x01;   
    
    TCNT0 = 0x00;
    OCR0 = 187;
    TIMSK = 0b00000010; // Compare match Interrupt
    TCCR0 = 0b00001011;
                       
    
    #asm("sei")
    
    while(1){}
}
