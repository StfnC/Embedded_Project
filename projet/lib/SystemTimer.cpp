/**
 * Implementation of the RobotProgramDownloader class
 * 
 * \file SystemTimer.cpp
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 * 
 *  Output:
 * 
 */


#include "SystemTimer.h"

#include <avr/interrupt.h>

uint32_t SystemTimer::timerCount_ = 0;

void SystemTimer::init() {
    cli();

    TCNT2 = 0;
    TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
    TCCR2B |= (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A);

    OCR2A = 0x00;

    sei();
}

void SystemTimer::start() {
    OCR2A = ONE_MS_WITH_32_PRESCALER;
}

void SystemTimer::stop() {
    cli();

    TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1));
    OCR2A = 0x0000;
    TIMSK2 &= ~(_BV(OCIE2A));

    sei();
}

void SystemTimer::incrementTimer() {
    timerCount_++;
}
