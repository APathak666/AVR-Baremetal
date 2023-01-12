//#define F_CPU 1000000
#include <avr/interrupt.h>
#include <util/delay.h>

int intFlag = 0;

int main(void)
{
    DDRB = (1 << PORTB0); //turn pin 8 on
    PORTB = (1 << PORTB0); //output mode

    PORTD = (1 << PORTD3); //set ISC0 and ISC1 pins

    EIMSK = (1 << INT1); //enable INT1

    sei(); //enable global interrupt

    while(1)
    {
        if (intFlag == 1) //in case of interrupt
        {
            PORTB ^= (1 << PORTB0); //toggle
            //sei();
            intFlag = 0; //reset interrupt flag
        }

        // else
        // {
        //     cli();
        //     _delay_ms(2000);
        //     intFlag = 0;
        // }

        _delay_ms(5000);
    }
}

ISR(INT1_vect)
{
//    PORTB ^= (1 << PORTB2);
    intFlag = 1; //notify that interrupt has been requested
}
