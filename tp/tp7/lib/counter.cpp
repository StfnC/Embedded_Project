#include "counter.h"
const uint16_t ONE_SECOND_PRESCALER_VALUE = 7812.5;

CounterInterrupt::CounterInterrupt() {
    cli();
    TCNT1 = 0;
    TCCR1C = 0;
    TCCR1B &= ~(_BV(CS11));
    TCCR1B |= _BV(CS12) | _BV(CS10);
    TIMSK1 = _BV(OCIE1A);
    sei();
}

void CounterInterrupt::setGenerationMode(GenerationMode generationMode) {
    cli();

    switch (generationMode) {
        case GenerationMode::Normal:
            TCCR1A &= ~(_BV(WGM10) | _BV(WGM11));
            TCCR1B &= ~(_BV(WGM11) | _BV(WGM12));
            TCCR1C = 0;
            break;

        case GenerationMode::ClearTimerCompare:
            TCCR1A &= ~(_BV(WGM10) | _BV(WGM11));
            TCCR1B &= ~(_BV(WGM13));
            TCCR1B |= _BV(WGM12);
            break;
    }

    sei();
}

void CounterInterrupt::setCompareMode(CompareMode compareMode) {
    cli();
    switch (compareMode) {
        case CompareMode::Toggle:
            TCCR1A &= ~(_BV(COM1A1));
            TCCR1A |= _BV(COM1A0);
            break;

        case CompareMode::SetToLow:
            TCCR1A &= ~(_BV(COM1A0));
            TCCR1A |= _BV(COM1A1);
            break;

        case CompareMode::SetToHigh:
            TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
            break;

        case CompareMode::Off:
            TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
            break;
    }

    sei();
}

void CounterInterrupt::setDuration(uint16_t duration) {
    uint16_t durationTimer = duration * ONE_SECOND_PRESCALER_VALUE;
    if (durationTimer <= 65535) {
        OCR1A = durationTimer;
    }
}