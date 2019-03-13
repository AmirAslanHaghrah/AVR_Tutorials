/*
 * LineFollower.cpp
 *
 * Created: 3/10/2019 5:01:10 PM
 * Author : amiraslan haghrah
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB = 0x00;
	DDRA = 0xFF;
	long M1Speed = 50;
	long M2Speed = 50;
	
	int sensorData = 0;
	    
    while (1) 
    {
		sensorData = PINB;
		for (long i = 0; i < 100; i++){
			if (i < M1Speed && i < M2Speed){
				PORTA = 0b000000011;
			}else if (i < M1Speed && i > M2Speed){
				PORTA = 0b000000001;
			}else if (i > M1Speed && i < M2Speed){
				PORTA = 0b000000010;
			}else{
				PORTA = 0b000000000;
			}
		}
		
    }
}
