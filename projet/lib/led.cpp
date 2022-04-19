/**
 * Implementation of the led methods
 * 
 * \file led.cpp
 * \author Lina Belloui and Stefan Cotargasanu
 * \date March 13 2022
 *
 */

#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "led.h"

#include <util/delay.h>

led::led(uint8_t pin1, uint8_t pin2) : pin1_(pin1), pin2_(pin2) {
    DDRA |= (1 << pin1_) | (1 << pin2_);
}

void led::setGreen() {
    PORTA |= (1 << pin1_);
    PORTA &= ~(1 << pin2_);
}

void led::setRed() {
    PORTA &= ~(1 << pin1_);
    PORTA |= (1 << pin2_);
}

void led::setOff() {
    PORTA &= ~((1 << pin2_) | (1 << pin1_));
}

void led::setAmber() {
    setGreen();
    _delay_ms(GREEN_AMBER_DELAY);
    setRed();
    _delay_ms(RED_AMBER_DELAY);
}