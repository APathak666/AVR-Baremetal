#define F_CPU 20000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int secondsCount = 0;

int main(void)
{
    DDRB = 0x01; //set LED to output

    // 8-bit mode
    // TCCR0A = (1 << WGM01); //set CTC bit
    // OCR0A =  195; //number of ticks
    // TIMSK0 = (1 << OCIE0A); //compare match A interrupt enable

    // sei(); //set global interrupt (I-bit)
    // TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00); //prescaler

    //16-bit mode

    TCCR1B =(1 << WGM12); //set CTC bit
    OCR1A = 19531; //number of ticks
    TIMSK1 = (1 << OCIE1A);  //enable compare match A interrupt 

    sei(); //enable global interrupt (I-bit)
    TCCR1B |= (1 << CS12) | (1 << CS10);
    while (1)
    {

    }
}

//8-bit ISR
ISR(TIMER0_COMPA_vect)
{
    secondsCount++;

    if (secondsCount == 100)
    {
        secondsCount = 0;
        PORTB ^= (1 << PORTB0);
    }
}

//16-bit ISR
ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << PORTB0);
}