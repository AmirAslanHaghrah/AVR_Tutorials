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
	bool LEDRed_F = false;
	bool LEDBlue_F = false;
	
	
	long Red = 0;
	long Green = 0;
	long Blue = 0;
    
    while (1) 
    {
		if((PINA & 0b00000001) == 0 && !LEDGreen_F){
			LEDGreen_F = true;			
			if (Green < 500){
				Green += 5;
			}			
		}
		if((PINA & 0b00000001) > 0){
			LEDGreen_F = false;	
		}
		
		if((PINA & 0b00000010) == 0 && !LEDRed_F){
			LEDRed_F = true;
			if (Red < 500){
				Red += 5;
			}
		}
		if((PINA & 0b00000010) > 0){
			LEDRed_F = false;
		}
		if((PINA & 0b00000100) == 0 && !LEDBlue_F){
			LEDBlue_F = true;
			if (Blue < 500){
				Blue += 5;
			}
		}
		if((PINA & 0b00000100) > 0){
			LEDBlue_F = false;
		}
		
		for (long i = 0; i < 500; i++){
			if (i < Green && i < Red && i < Blue){
				PORTD = 0b11111000;
			}else if(i > Green && i < Red && i < Blue){
				PORTD = 0b11111001;
			}else if(i < Green && i > Red && i < Blue){
				PORTD = 0b11111100;
			}else if(i < Green && i < Red && i > Blue){
				PORTD = 0b11111010;
			}else if(i > Green && i > Red && i < Blue){
				PORTD = 0b11111101;
			}else if(i > Green && i < Red && i > Blue){
				PORTD = 0b11111011;
			}else if(i < Green && i > Red && i > Blue){
				PORTD = 0b11111110;
			}else{
				PORTD = 0b11111111;
			}
		}
		
    }
}
