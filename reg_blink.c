#define DRegB *((unsigned char*) 0x25)
//#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	DDRB = (1 << PORTB0);
	PORTB = 1;

	while (1)
	{
		DRegB |= (1<<2);
		_delay_ms(1000);
		DRegB &= ~(1<<2);
		_delay_ms(1000);
	}	
}
