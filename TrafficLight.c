#include <io.h>

void UpdateTF();

int deci = 0;
int sec = 0;
 
int GreenTime = 10;

// 0 -> Red
// 1 -> Yellow
// 2 -> Green 
int TF_status = 0;

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void){
    if ( deci < 100){
        deci++;
    }else{
        deci = 0;
        sec++;
    } 
    UpdateTF();                   
}

void UpdateTF(){
     if ( TF_status == 0 && sec == 5){
        TF_status = 2;
        PORTC = 0b00001100;
        deci = 0;
        sec = 0;
    }    
    if (TF_status == 2 && sec == GreenTime){
        TF_status = 1;
        PORTC = 0b00001010;
        deci = 0;
        sec = 0;
    }    
    if (TF_status == 1 && sec == 5){
        TF_status = 2;
        PORTC = 0b00010001;
        deci = 0;
        sec = 0;
    }
}

void main(){
    DDRC = 0xFF;    
    
    TCNT0 = 0x00;
    OCR0 = 155;
    TIMSK = 0b00000010;
    TCCR0 = 0b00001100; 
    
    TF_status = 2;
    PORTC = 0b00001100;
    
    #asm("sei");     
    while(1){}
}
