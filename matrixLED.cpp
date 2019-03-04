/*
 * MatrixLED.cpp
 *
 * Created: 3/3/2019 2:38:26 PM
 * Author : amiraslan haghrah
 */ 
#include <avr/io.h>
void TurnLEDon(int x, int y);
int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;			
	int X_ball = 2;
	int Y_ball = 6;	
	int X_step = +1;
	int Y_step = +1;	
	int X_max = 8;
	int Y_max = 8;			    
    while (1) 
    {
		if (X_ball == X_max){
			X_step = -1;
		}
		if (X_ball == 1){
			X_step = +1;
		}				
		if (Y_ball == Y_max){
			Y_step = -1;
		}
		if (Y_ball == 1){
			Y_step = +1;
		}		
		X_ball += X_step;
		Y_ball += Y_step;		
		TurnLEDon(X_ball, Y_ball);		
		for(long i = 0 ; i < 100000; i++){};
    }
}
void TurnLEDon(int x, int y){
	PORTC = 1 << (x - 1) ;
	PORTD = ~(1 << (y - 1));	
}

