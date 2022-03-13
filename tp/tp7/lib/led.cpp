/**
 * Implementation of the led methods
 * 
 * \file led.cpp
 * \author Lina Belloui and Stefan Cotargasanu
 * \date March 13 2022
 *
 */

#include "led.h"

#include <util/delay.h>

led::led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2) : port_(port), pin1_(pin1), pin2_(pin2) {
}

void led::setGreen() {
    *port_ |= (1 << pin1_);
    *port_ &= ~(1 << pin2_);
}

void led::setRed() {
    *port_ &= ~(1 << pin1_);
    *port_ |= (1 << pin2_);
}

void led::setOff() {
    *port_ &= ~((1 << pin2_) | (1 << pin1_));
}

void led::setAmber() {
    setGreen();
    _delay_ms(GREEN_AMBER_DELAY);
    setRed();
    _delay_ms(RED_AMBER_DELAY);
}