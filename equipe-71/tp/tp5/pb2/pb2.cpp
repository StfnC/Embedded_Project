#define F_CPU 8000000

#include <avr/io.h>

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

    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 20; j++) {
            transmissionUART(mots[j]);
        }
    }

    return 0;
}