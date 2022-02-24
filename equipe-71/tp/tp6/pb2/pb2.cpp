/**
 * Second problem of the TP6
 * This code continuously reads the analog value coming in the pin A0 and converts it to a value between 0 and 255.
 * If the value is below LOW_LIGHT_THRESHOLD, the LED turns green.
 * If it's above STRONG_LIGHT_THRESHOLD, the led turns red.
 * If it's in between these thresholds, we cycle through red and green to make the LED look amber.
 * 
 * \file pb2.cpp
 * \author Stefan Cotargasanu and Justine Sauquet
 * \date February 21 2022
 * 
 * Pins:
 *  Input:
 *      -A0
 *  Output:
 *      -B0
 *      -B1
 * 
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#include "can.h"

const uint8_t LOW_LIGHT_THRESHOLD = 150;
const uint8_t STRONG_LIGHT_THRESHOLD = 230;
const uint8_t AMBER_RED_DELAY = 10;
const uint8_t AMBER_GREEN_DELAY = 18;
const uint8_t ADC_POSITION = 0;
const uint8_t PRECISION_LOSS = 2;

void initialization() {
    DDRA &= ~(1 << DDA0);
    DDRB |= (1 << DDB0) | (1 << DDB1);
}

void lightRedLed() {
    PORTB &= ~(1 << DDB0);
    PORTB |= 1 << DDB1;
}

void lightGreenLed() {
    PORTB |= 1 << DDB0;
    PORTB &= ~(1 << DDB1);
}

void lightLedAmber() {
    lightRedLed();
    _delay_ms(AMBER_RED_DELAY);
    lightGreenLed();
    _delay_ms(AMBER_GREEN_DELAY);
}

int main() {
    initialization();

    can analogToDigitalConverter;
    uint8_t analogReading = 0;

    while (true) {
        analogReading = static_cast<uint8_t>(analogToDigitalConverter.lecture(ADC_POSITION) >> PRECISION_LOSS);

        if (analogReading > STRONG_LIGHT_THRESHOLD) {
            lightRedLed();
        } else if (analogReading < LOW_LIGHT_THRESHOLD) {
            lightGreenLed();
        } else {
            lightLedAmber();
        }
    }

    return 0;
}