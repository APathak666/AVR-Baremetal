#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle = 0;

int main(void)
{
    DDRD = (1 << PORTD6); //turn PWM pin 6 on

    TCCR0A = (1 << WGM01) | (1 << WGM00); //set timer in fast PWM mode
    TCCR0A = (1 << COM0A1); //clear timer on compare match, set OC0A at bottom
    
    sei(); //set external interrupts
    
    TCCR0B = (1 << CS00) | (1 << CS02); //set prescaler to 1

    while(1)
    {

    }
}

ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100)*255;
}