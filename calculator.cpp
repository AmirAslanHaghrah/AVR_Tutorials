/*
 * Calculator.cpp
 *
 * Created: 10/20/2019 2:12:32 PM
 * Author : amir aslan haghrah
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

void RefreshDisplay(int n);
int digit[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b00111110, 0b11100000, 0b11111110, 0b11110110};	

int input1 = 0;
bool key1down = false;
bool key2down = false;

int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;				
    while (1) 
    {
		if((PINA & 0b00000001) > 0  && !key1down){
			key1down = true;			
			input1 = input1 * 10 + 1;
		}
		if((PINA & 0b00000001) == 0  && key1down){
			key1down = false;			
		}
		
		if((PINA & 0b00000010) > 0 && !key2down){
			key2down = true;
			input1 = input1 * 10 + 2;
		}
		if((PINA & 0b00000010) == 0  && key2down){
			key2down = false;
		}
		
		RefreshDisplay(input1);			
    }
}

void RefreshDisplay(int n){
	int i = 0;
	while(n > 0){
		PORTC = 0x00;		
		PORTD = ~(0b00000001 << i);
		PORTC = digit[n%10];
		_delay_us(10);
		n=n/10;
		i++;
	}		
}

