
#include "transmission.h"

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    UCSR0A |= (1 << RXC0) | ( 1 << TXC0);

    UCSR0B |= (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// Du USART vers le PC

void transmissionUART(uint8_t donnee)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = donnee;
}

uint8_t USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1 << RXC0)))
        ;
    /* Get and return received data from buffer */
    return UDR0;
}

int main()
{
    initialisationUART();
    Memoire24CXXX memory = Memoire24CXXX();
    memory.ecriture(startAdress, &mot[0], longueur);
    _delay_ms(10);
    uint8_t *memoryRead;
    memory.lecture(startAdress, memoryRead, longueur);
    _delay_ms(10);

    while (true)
    {
        for (uint8_t i = 0; i < longueur; i++)
        {
            transmissionUART(memoryRead[i]);
        }
    }
}
