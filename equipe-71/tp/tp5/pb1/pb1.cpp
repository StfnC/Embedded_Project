#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "memoire_24.h"

const uint16_t START_OF_CHAIN = 0x0000;
const uint8_t LENGTH_OF_CHARACTER_CHAIN = 46;
uint8_t CHARACTER_CHAIN[LENGTH_OF_CHARACTER_CHAIN] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";

void initialisation() {
    cli();

    DDRA |= (1 << DDA0) | (1 << DDA1);

    sei();
}

bool validateChain(uint8_t* chainToValidate, uint8_t lengthOfChain) {
    bool valid = true;

    for (uint8_t i = 0; i < lengthOfChain; i++) {
        valid &= CHARACTER_CHAIN[i] == chainToValidate[i];
    }

    return valid;
}

int main() {
    initialisation();
    Memoire24CXXX memory;

    memory.ecriture(START_OF_CHAIN, &CHARACTER_CHAIN[0], LENGTH_OF_CHARACTER_CHAIN);
    memory.ecriture(START_OF_CHAIN + LENGTH_OF_CHARACTER_CHAIN * sizeof(uint8_t), 0xFF);

    uint8_t chainInMemory[LENGTH_OF_CHARACTER_CHAIN];
    memory.lecture(START_OF_CHAIN, &chainInMemory[0], LENGTH_OF_CHARACTER_CHAIN);

    if (validateChain(chainInMemory, LENGTH_OF_CHARACTER_CHAIN)) {
        PORTA |= (1 << DDA0);
    } else {
        PORTA |= (1 << DDA1);
    }

    return 0;
}