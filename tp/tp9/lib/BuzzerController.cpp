#include "BuzzerController.h"
#include <math.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

void BuzzerController::initBuzzer() {
    OCR1A = 0x0000;
    TCCR1B |= (1 << CS11) | (1 << WGM12);
}

void BuzzerController::playNote(uint8_t note) {
    DDRD |= (1 << DDD5) | (1 << DDD4);
    TCCR1A |= (1 << COM1A0);

    uint16_t frequency = 440 * pow(2, (note - 69) / 12);
    uint16_t ocr = F_CPU / (2 * 1024 * frequency) - 1;

    OCR1A = ocr;

    TCNT1 = 0x0000;
}

void BuzzerController::stopNote() {
    TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
    OCR1A = 0x0000;
}
