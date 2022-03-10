#include "counter.h"
const uint8_t ONE_SECOND_PRESCALER_VALUE = 7812.5;


CounterInterrupt::CounterInterrupt()
{
    TCCR1C = 0;
    TCCR1B &= ~(_BV(CS11));
    TCCR1B |= _BV(CS12) | _BV(CS10);
} 

void CounterInterrupt::setNormal()
{
    TCCR1A &= ~(_BV(WGM10) | _BV(WGM11));
    TCCR1B &= ~(_BV(WGM11) | _BV(WGM12));
    TCCR1C  = 0;
}

void CounterInterrupt::setCtc()
{
    TCCR1A &= ~(_BV(WGM10) | _BV(WGM11));
    TCCR1B &= ~(_BV(WGM13));
    TCCR1B |= _BV(WGM12);
}

void CounterInterrupt::setToggle()
{
    TCCR1A &= ~(_BV(COM1A1));
    TCCR1A |= _BV(COM1A0);
}

void CounterInterrupt::setToLow()
{
    TCCR1A &= ~(_BV(COM1A0));
    TCCR1A |= _BV(COM1A1);
}

void CounterInterrupt::setToHigh()
{
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
}

void CounterInterrupt::setOff()
{
    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
}

void setDuration(uint8_t duration)
{
    uint8_t durationTimer = duration * ONE_SECOND_PRESCALER_VALUE;
    OCR1A = durationTimer;
}
