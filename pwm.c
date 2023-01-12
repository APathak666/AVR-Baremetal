#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle = 0;

void ADCsetup(void);
void startConversion(void);

int main(void)
{
    DDRD = (1 << PORTD6); //turn PWM pin 6 on

    TCCR0A = (1 << WGM01) | (1 << WGM00); //set timer in fast PWM mode
    TCCR0A = (1 << COM0A1); //clear timer on compare match, set OC0A at bottom
    
    OCR0A = (dutyCycle/100)*255; //set comparison register according to duty cycle

    sei(); //set external interrupts

    TCCR0B = (1 << CS00) | (1 << CS02); //set prescaler to 1

    while(1)
    {
        _delay_ms(100);
        dutyCycle += 10;

        if (dutyCycle == 100)
            dutyCycle = 0;
    }
}

void ADCsetup(void)
{
    ADMUX = (1 << RESF0); //AVcc with external capacitor at AREF pin
    ADMUX |= (1 << MUX0) | (1 << MUX0); //select ADC pin 5
    ADCSRA = (1 << ADEN); //enable ADC
    ADCSRA |= (1 << ADIE); //trigger interrupt every time ADC finished conversion
    ADCSRA |= (1 << ADPS0) | (1 << ADPS2); //prescaler factor of 128
}

void startConversion(void)
{

}

ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100)*255; //reset the duty cycle
}