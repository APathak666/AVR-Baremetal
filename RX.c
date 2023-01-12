#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/BAUD/16) - 1)
#define RX_BUFFER_SIZE 128

#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

char rxBuffer[RX_BUFFER_SIZE];

uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

char getChar(void);
char peekChar(void);

int main(void)
{
    char control;

    UBRR0H = (BRC >> 8); //load top 8 bits of BRC into UBRR0H
    UBRR0L = BRC; //load lower 8 bits of BRC into UBRR0L

    UCSR0B = (1 << RXEN0); //enable RX receive 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //set up 8 bit data frame

    UCSR0B |= (1 << RXCIE0); //enable USART receive complete interrupt

    DDRB = (1 << PORTB0);

    sei();
    while (1)
    {
        control = getChar();

        if (control == 0)
            sbi(PORTB, PORTB0);

        else if (control == 1)
            cbi(PORTB, PORTB0);
    }
}

char getChar(void)
{
    char ret = '\0';

    if (rxReadPos != rxWritePos)
    {
        ret = rxBuffer[rxReadPos];
        rxReadPos = (rxReadPos + 1)%RX_BUFFER_SIZE;
    }

    return ret;
}

char peekChar(void)
{
    char ret = '\0';

    if (rxReadPos != rxWritePos)
        ret = rxBuffer[rxReadPos];

    return ret;
}

ISR(USART_RX_vect)
{
    rxBuffer[rxWritePos] = UDR0;
    rxWritePos = (rxWritePos + 1)%RX_BUFFER_SIZE;
}
