/**
 * Implementation of the CounterInterrupt methods
 * 
 * \file counter.cpp
 * \author Faneva Rakotoarivony
 * \date March 13 2022
 *
 */

#include "counter.h"

CounterInterrupt::CounterInterrupt() {
    cli();
    TCNT1 = 0;
    TCCR1C = 0;
    TCCR1B &= ~((1 << CS11));
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 = (1 << OCIE1A);
    sei();
}

void CounterInterrupt::setGenerationMode(GenerationMode generationMode) {
    cli();

    switch (generationMode) {
        case GenerationMode::Normal:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
            TCCR1C = 0;
            break;

        case GenerationMode::ClearTimerCompare:
            TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
            TCCR1B &= ~((1 << WGM13));
            TCCR1B |= (1 << WGM12);
            break;
    }

    sei();
}

void CounterInterrupt::setCompareMode(CompareMode compareMode) {
    cli();
    switch (compareMode) {
        case CompareMode::Toggle:
            TCCR1A &= ~((1 << COM1A1));
            TCCR1A |= (1 << COM1A0);
            break;

        case CompareMode::SetToLow:
            TCCR1A &= ~((1 << COM1A0));
            TCCR1A |= (1 << COM1A1);
            break;

        case CompareMode::SetToHigh:
            TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
            break;

        case CompareMode::Off:
            TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
            break;
    }

    sei();
}

void CounterInterrupt::setDuration(uint16_t duration) {
    uint16_t durationTimer = duration * ONE_SECOND_PRESCALER_VALUE;
    if (durationTimer <= UINT16_MAX) {
        OCR1A = durationTimer;
    }
}