/*
 * MotorDrive.cpp
 *
 * Created: 3/3/2019 3:18:02 PM
 * Author : amiraslan haghrah
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA = 0x00;
	DDRD = 0xFF;
	bool LEDGreen_F = false;
	
	long speed = 0;
    /* Replace with your application code */
    while (1) 
    {
		if((PINA & 0b00000001) == 0 && !LEDGreen_F){
			LEDGreen_F = true;			
			if (speed < 500){
				speed += 5;
			}			
		}
		if((PINA & 0b00000001) > 0){
			LEDGreen_F = false;	
		}
		
		for (long i = 0; i < 500; i++){
			if (i < speed){
				PORTD = 0b11111110;
			}else{
				PORTD = 0b11111111;
			}
		}
    }
}

