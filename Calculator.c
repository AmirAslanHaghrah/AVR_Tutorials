/*
 * GccApplication2.c
 *
 * Created: 23/10/2018 07:30:18 ب.ظ
 * Author : SAJJAD
 */ 
#include <avr/io.h>

int main(void)
{
	int x=-1,y,math,answer;   
    while (1){
		DDRA = 0b11111111;
		DDRB = 0b11111111;
		DDRC = 0B00000000;
		DDRD = 0b00000000;
		
		int i=0;
		int slice[4]={0,0,0,0};
		if(PINC == 0b00000001){
			while(PINC == 0b00000001){}
			if(x==-1)
				x=0;
			else
				x=(x*10)+0;
			}
		if(PINC == 0b00000010){
			while(PINC == 0b00000010){}
			if(x==-1)
				x=1;
			else
				x=(x*10)+1;
		}
		if(PINC == 0b00000100){
			while(PINC == 0b00000100){}
			if(x==-1)
				x=2;
			else
				x=(x*10)+2;
		}
		if(PINC == 0b00001000){
			while(PINC == 0b00001000){}
			if(x==-1)
				x=3;
			else
				x=(x*10)+3;
		}
		if(PINC == 0b00010000){
			while(PINC == 0b00010000){}
			if(x==-1)
				x=4;
			else
				x=(x*10)+4;
		}
		if(PINC == 0b00100000){
			while(PINC == 0b00100000){}
			if(x==-1)
				x=5;
			else
				x=(x*10)+5;
		}
		if(PINC == 0b01000000){
			while(PINC == 0b01000000){}
			if(x==-1)
				x=6;
			else
				x=(x*10)+6;
		}
		if(PINC == 0b10000000){
			while(PINC == 0b10000000){}
			if(x==-1)
				x=7;
			else
				x=(x*10)+7;
		}
		
		if(PIND == 0b00000001){
			while(PIND == 0b00000001){}
			if(x==-1)
			x=8;
			else
			x=(x*10)+8;
		}
		if(PIND == 0b00000010){
			while(PIND == 0b00000010){}
			if(x==-1)
			x=9;
			else
			x=(x*10)+9;
		}
		if(PIND == 0b00000100){
			while(PIND == 0b00000100){}
				//+
			math=1;
			answer=x;
			x=0;
		}
		if(PIND == 0b00001000){
			while(PIND == 0b00001000){}
				//-
			math=2;
			answer=x;
			x=0;
			}
			
			if(PIND == 0b00010000){
				while(PIND == 0b00010000){}
					//*
				math=3;
				answer=x;
				x=0;
			}
		
		if(PIND == 0b00100000){
			while(PIND == 0b00100000){}
				// /
			math=4;
			answer=x;
			x=0;
		}
		if(PIND == 0b01000000){
			while(PIND == 0b01000000){}
			//=
			switch(math){
			case 1:
			x=x+answer;
			break;
			case 2:
			x=answer-x;
			break;
			case 3:
			x=answer*x;
			break;
			case 4:
			x=answer/x;
			break;	
			}	
		}
		
		if(PIND == 0b10000000){
			x=-1;
			answer=0;
			math=0;
		}
		
		y=x;
		while(1){
			slice[i]=y%10;
			y=y/10;
			if(y<10){
				i++;
				slice[i]=y;
				break;
			}
		i++;	
		}
		PORTA=slice[0]+slice[1]*16;
		PORTB = slice[2]+slice[3]*16;
	} 
		}
		

