#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "memoire_24.h"

void initialisationUART();

void initialisation() {
    initialisationUART();
}

void initialisationUART() {
    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0B |= (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

// Du USART vers le PC

void transmissionUART(uint8_t donnee) {
    // Copy pasted from p.174 of the ATmega documentation

    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main() {
    initialisation();

    Memoire24CXXX memory;
    const uint8_t LENGTH = 18;
    uint8_t words[LENGTH] = "UNLIMITED POWER!\n";

    memory.ecriture(0x0000, &words[0], LENGTH);
    _delay_ms(5);
    memory.ecriture(0x0000 + LENGTH * sizeof(uint8_t), 0xFF);
    _delay_ms(5);

    uint8_t counter = 0;
    uint8_t* valueInMemory;

    while (*valueInMemory != 0xFF) {
        memory.lecture(0x0000 + counter * sizeof(uint8_t), valueInMemory);
        _delay_ms(5);
        transmissionUART(*valueInMemory);
        counter++;
    }

    return 0;
}