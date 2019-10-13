/*
 * Week12.cpp
 *
 * Created: 10/6/2019 2:18:19 PM
 * Author : AmirAslan Haghrah
 */ 

#include <avr/io.h>

void refreshDisplay(int *display);

int main()
{
    DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;	
	int display [16] ={};
	int tmpdisplay [16] ={};	
		
	display[0] =  0b00000000;
	display[1] =  0b00111100;
	display[2] =  0b01100110;
	display[3] =  0b01100110;
	display[4] =  0b01111110;
	display[5] =  0b01100110;
	display[6] =  0b01100110;
	display[7] =  0b00000000;
	display[8] =  0b00000000;
	display[9] =  0b00000000;
	display[10] = 0b00000000;
	display[11] = 0b00011000;
	display[12] = 0b00000000;
	display[13] = 0b00000000;
	display[14] = 0b00000000;
	display[15] = 0b00000000;

	PORTB = 0x00;
	PORTC = 0x00;
	
	while(1){
		
		for (int r = 0; r < 16; r++){
			if ( r == 15){
				tmpdisplay[r] = display[0];	
			}else{
				tmpdisplay[r] = display[r + 1];	
			}			
		}
		for(int i = 0; i < 16; i++){
			display[i] = tmpdisplay[i];
		}
						
		refreshDisplay(display);
		for(long int d = 0; d<3000; d++){}
	}
}

void refreshDisplay(int *display){
	for ( int i = 0; i < 8; i ++){
		PORTB = (1 << i);
		PORTD = ~display[i];
		for(int d=0; d < 300; d++)	{}
	}
	PORTB = 0x00;
	for ( int i = 8; i < 16; i ++){
		PORTC = (1 << (i - 8));
		PORTD = ~display[i];
		for(int d=0; d < 300; d++)	{}
	}
	PORTC = 0x00;
}
