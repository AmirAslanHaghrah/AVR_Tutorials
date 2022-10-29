/*
 * ping-pong.cpp
 *
 * Created: 10/29/2022 10:40:08 AM
 * Author : amira
 */ 
#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

void render_ball(uint8_t x, uint8_t y);
void render_rocket_player1(uint8_t y);
void render_rocket_player2(uint8_t y);
void refresh();
void check_inputs();
void check_points();

uint8_t digits[10] = {
	0b0111111, //-> 0
	0b0000110, //-> 1
	0b1011011, //-> 2
	0b1001111, //-> 3
	0b1100110, //-> 4
	0b1101101, //-> 5
	0b1111100, //-> 6
	0b0000111, //-> 7
	0b1111111, //-> 8
	0b1101111, //-> 9
};

int r = 0;

uint8_t P1_y = 2;
uint8_t P2_y = 2;

uint8_t ball_x = 7;
uint8_t ball_y = 4;
uint8_t stepX = +1;
uint8_t stepY = -1;

bool P1_Uph = false;
bool P1_Downh = false;

bool P2_Uph = false;
bool P2_Downh = false;

uint8_t P1_points = 0;
uint8_t P2_points = 0;

int main(void)
{
	DDRA = 0xff;
	DDRB = 0b00001100;
	DDRC = 0xff;
	DDRD = 0xff;
	
    /* Replace with your application code */
    while (1) 
    {
		r++;		
			
		PORTC = 0x00;
		PORTD = 0x00;
		PORTB = PORTB & ~0b00001100;
		PORTB = PORTB |  0b00000100;
		PORTA = ~digits[P1_points];
		_delay_ms(10);
		PORTB = PORTB & ~0b00001100;
		PORTB = PORTB |  0b00001000;
		PORTA = ~digits[P2_points];
		_delay_ms(10);
		
		check_inputs();	
		refresh();
		
		PORTB = PORTB & ~0b00011000;
		render_rocket_player1(P1_y);
		_delay_ms(5);
		render_rocket_player2(P2_y);
		_delay_ms(5);
		render_ball(ball_x, ball_y);
		_delay_ms(5);
    }
}

void render_ball(uint8_t x, uint8_t y)
{
	if (x < 8)
	{
		PORTC = 0b00000001 << x;
		PORTD = 0x00;
	}
	else
	{
		PORTC = 0x00;
		PORTD = 0b00000001 << (x - 8);
	}
	PORTA = ~(0b00000001 << y);	
}

void render_rocket_player1(uint8_t y)
{
	PORTD = 0x00;
	PORTC = 0b00000001;
	PORTA = ~(0b00001111 << y);
}

void render_rocket_player2(uint8_t y)
{
	PORTC = 0x00;
	PORTD = 0b10000000;
	PORTA = ~(0b00001111 << y);
}

void refresh()
{
	if (r == 10)
	{
		if (ball_y == 0)
		{
			stepY = +1;
		}
		if (ball_y == 7)
		{
			stepY = -1;
		}
		if (ball_x == 1)
		{
			stepX = +1;
		}
		if (ball_x == 14)
		{
			stepX = -1;
		}
		ball_x = ball_x + stepX;
		ball_y = ball_y + stepY;
		r = 0;
		
		check_points();		
	}
}

void check_inputs()
{
	
	if ( (PINB & 0b00000001) == 0b00000001 && P1_Uph == false)
	{
		P1_Uph = true;
		P1_y --;
	}
	if ((PINB & 0b00000001) == 0b00000000)
	{
		P1_Uph = false;
	}
	
	if ( (PINB & 0b00000010) == 0b00000010 && P1_Downh == false)
	{
		P1_Downh = true;
		P1_y ++;
	}
	if ((PINB & 0b00000010) == 0b00000000)
	{
		P1_Downh = false;
	}
	
	
	if ((PINB & 0b10000000) == 0b10000000 && P2_Uph == false)
	{
		P2_Uph = true;
		P2_y ++;
	}
	if ((PINB & 0b10000000) == 0b00000000)
	{
		P2_Uph = false;
	}
	
	if ( (PINB & 0b01000000) == 0b01000000 && P2_Downh == false)
	{
		P2_Downh = true;
		P2_y --;
	}
	if ((PINB & 0b01000000) == 0b00000000)
	{
		P2_Downh = false;
	}
}

void check_points()
{
	if (ball_x == 1)
	{
		if (ball_y < P1_y || ball_y > P1_y + 4)
		{
			P2_points++;
		}
	}
	
	if (ball_x == 14)
	{
		if (ball_y < P2_y || ball_y > P2_y + 4)
		{
			P1_points++;
		}
	}
}
