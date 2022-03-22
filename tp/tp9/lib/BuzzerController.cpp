/**
 * Implementation of the MotorsController methods
 *
 * \file MotorsController.cpp
 * \author Stefan Cotargasanu
 * \date March 13 2022
 *
 * Pins:
 *  Input:
 *      -
 *
 *  Output:
 *      -D4
 *      -D5
 *
 */

#include "BuzzerController.h"

#include <math.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

// Calculated using the formula from p.96 of ATmega documentation
const uint16_t BuzzerController::OCR_VALUES[] = {
    4545,
    4290,
    4050,
    3822,
    3608,
    3405,
    3214,
    3034,
    2863,
    2703,
    2551,
    2408,
    2273,
    2145,
    2025,
    1911,
    1804,
    1703,
    1607,
    1517,
    1432,
    1351,
    1276,
    1204,
    1136,
    1073,
    1012,
    956,
    902,
    851,
    804,
    758,
    716,
    676,
    638,
    602,
    568};

void BuzzerController::initBuzzer() {
    DDRD |= (1 << DDD5) | (1 << DDD4);
    OCR1A = 0x0000;
    TCCR1B |= (1 << CS11) | (1 << WGM12);
}

void BuzzerController::playNote(uint8_t note) {
    TCCR1A |= (1 << COM1A0);

    OCR1A = OCR_VALUES[note - 45];

    TCNT1 = 0x0000;
}

void BuzzerController::stopNote() {
    TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
    OCR1A = 0x0000;
}
