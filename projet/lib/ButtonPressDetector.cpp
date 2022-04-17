#define F_CPU 8000000L

#include "ButtonPressDetector.h"

#include <avr/interrupt.h>
#include <util/delay.h>

// FIXME: In the header, specify that this class is meant to detect a single press
//        The user of this class is expected to set the press detected to false when it wants to detect another press
//        This also assumes the person that pressed the button doesn't hold the button pressed

ISR(INT0_vect) {
    _delay_ms(ButtonPressDetector::getDebounceTime());

    ButtonPressDetector::setSmallButtonPressed(true);
}

ISR(INT1_vect) {
    _delay_ms(ButtonPressDetector::getDebounceTime());

    ButtonPressDetector::setBreadButtonPressed(true);
}

bool ButtonPressDetector::breadButtonWasPressed_ = false;
bool ButtonPressDetector::smallButtonWasPressed_ = false;

void ButtonPressDetector::init() {
    cli();

    DDRD &= ~((1 << DDD2) | (1 << DDD3));
    EIMSK |= (1 << INT0) | (1 << INT1);

    // Since the small button works by letting current through when the button is pressed and
    // the breadboard button works by not letting current when the button is pressed,
    // the interrupts need to be configured differently
    EICRA |= (1 << ISC00) | (1 << ISC01);
    EICRA |= (1 << ISC10) | (1 << ISC11);

    sei();
}

bool ButtonPressDetector::wasBreadButtonPressed() {
    return breadButtonWasPressed_;
}

bool ButtonPressDetector::wasSmallButtonPressed() {
    return smallButtonWasPressed_;
}

void ButtonPressDetector::setBreadButtonPressed(bool pressed) {
    breadButtonWasPressed_ = pressed;
}

void ButtonPressDetector::setSmallButtonPressed(bool pressed) {
    smallButtonWasPressed_ = pressed;
}
