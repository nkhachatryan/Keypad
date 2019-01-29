/*
 * GccApplication7.c
 *
 * Created: 29.01.2019 14:05:14
 * Author : nhac3
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t T = 0;
ISR (TIMER1_COMPA_vect)
{
	T = 1;
}

char opros_str_stolb(char N)
{
	if(N == 1)
	{
		DDRB = 0xF0; 
		PORTB = 0x0F;
		if (PINB != 0x0F);
		{
			return (~PINB) & 0x0F;;
		}
	} else
	{
		DDRB = 0x0F;
		PORTB = 0xF0;
		if (PINB != 0xF0);
		{
			return (~PINB) & 0xF0;;
		}
	}
}

char opros()
{
	char Z;
	Z = opros_str_stolb(0);
	Z << 4;
	Z |= opros_str_stolb(1);
	return Z;
}

/*char sootc(char kod)
{
	switch (kod)
	{
		case 0b10000001 : return 1;
		case 0b01000001 : return 2;
		case 0b00100001 : return 3;
		case 0b00010001 : return 4;
		case 0b10000010 : return 5;
		case 0b01000010 : return 6;
		case 0b00100010 : return 7;
		case 0b00010010 : return 8;
		case 0b10000100 : return 9;
		case 0b01000100 : return 10;
		case 0b00100100 : return 11;
		case 0b00010100 : return 12;
		case 0b10001000 : return 13;
		case 0b01001000 : return 14;
		case 0b00101000 : return 15;
		case 0b00011000 : return 16;
	}
}
*/
int main(void)
{
    TCCR1B |= (1<<WGM12); //reset by same
	TIMSK0 |= (1<<OCIE1A);
	OCR1AH = 0b00000011;
	OCR1AL = 0b11111111;
	TCCR1B |= (1<<CS11);
	DDRD = 0xFF;
	PORTD = 0x00;
	sei();
	char E = 0;
    while (1) 
    {
		T = 1;
		if(T)
		{
			T = 0;
			E = opros();
			if(E)
			{
				PORTD = E;
			}
		}
    }
}

