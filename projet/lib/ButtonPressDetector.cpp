/**
 * Define methods of ButtonPressDetector Class
 * 
 * \file ButtonPressDetector.cpp
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 *      Motherboard Button:
 *          -D2
 *      Breadboard Button:
 *          -D3
 *  Output:
 * 
 */


#define F_CPU 8000000L

#include "ButtonPressDetector.h"

#include <util/delay.h>

void ButtonPressDetector::init() {
    DDRD &= ~((1 << DDD2) | (1 << DDD3));

}

bool ButtonPressDetector::isBreadButtonPressed() {
    bool pressed = ~PIND & (1 << DDD3);

    if (pressed) {
        _delay_ms(DEBOUNCE_TIME);
        return ~PIND & (1 << DDD3);
    }
    return false;
}

bool ButtonPressDetector::isSmallButtonPressed() {
    bool pressed = PIND & (1 << DDD2);

    if (pressed) {
        _delay_ms(DEBOUNCE_TIME);
        return PIND & (1 << DDD2);
    }
    return false;
}
