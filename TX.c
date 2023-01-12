#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/BAUD/16) - 1)
#define TX_BUFFER_SIZE 128

char serialBuffer[TX_BUFFER_SIZE];

uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

void appendSerial(char c);
void serialWrite(char c[]);

int main(void)
{
    char control;

    UBRR0H = (BRC >> 8); //load top 8 bits of BRC into UBRR0H
    UBRR0L = BRC; //load lower 8 bits of BRC into UBRR0L

    UCSR0B = (1 << TXEN0); //enable TX transmission 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  //set up 8 bit data frame

    UCSR0B |= (1 << TXCIE0); //enable USART transmit complete interrupt

    DDRB = (1 << PORTB0);

    sei();

    serialWrite("Hello World\n");

    while (1)
    {
         UDR0 = '8'; //transmit char
         _delay_ms(1000);
    }
}

//transfer character from memory to serialBuffer
void appendSerial(char c)
{
    serialBuffer[serialWritePos] = c;
    serialWritePos = (serialWritePos + 1)%TX_BUFFER_SIZE;
}

//transfer entire string into serialBuffer using appendSerial
void serialWrite(char c[])
{
    for (uint8_t i = 0; i < strlen(c); i++)
        appendSerial(c[i]);

    if (UCSR0A & (1 << UDRE0))
        UDR0 = 0;
}

//transfer character from serialBuffer to UDR0 reg
ISR(USART_TX_vect)
{
    if(serialReadPos != serialWritePos)
        UDR0 = serialBuffer[serialReadPos];

    serialReadPos = (serialReadPos + 1)%TX_BUFFER_SIZE;
}
//Where is data being transmitted?
//When is USART_INT_vect being fired?
//Doesn't %TX_BUFFER_SIZE overwrite?