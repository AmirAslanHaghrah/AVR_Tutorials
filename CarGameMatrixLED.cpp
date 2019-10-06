/*
 * CarGameMatrixLED.cpp
 *
 * Created: 10/6/2019 2:18:19 PM
 * Author : AmirAslan Haghrah
 */ 

#include <avr/io.h>


int main()
{
    DDRC = 0xFF;
	DDRD = 0xFF;	
	int display [8] ={};
		
	display[0] = 0b00000000;
	display[1] = 0b00000000;
	display[2] = 0b00000000;
	display[3] = 0b00000000;
	display[4] = 0b00011000;
	display[5] = 0b00111100;
	display[6] = 0b00011000;
	display[7] = 0b00111100;

    while (1)
    {					
		  for ( int i = 0; i < 8; i ++){
			  PORTC = (1 << i);			
			  PORTD = ~display[i];
			  for(int d=0; d < 30000; d++)	{}
		  }
    }
}

