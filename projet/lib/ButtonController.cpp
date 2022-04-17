#define F_CPU 8000000L

#include "ButtonController.h"

#include <avr/interrupt.h>
#include <util/delay.h>

// FIXME: CRITICAL : WHEN POWERING UP THE CARD, THERE IS AN INTERRUPT FOR THE BREADBOARD BUTTON
//                   This is because it works by letting current through when not pressed
//                   Since there isn't current when the board is powered down, on powering up, it can generate an interrupt because the signal jumps from low to high

ISR(INT0_vect) {
    _delay_ms(ButtonController::getDebounceTime());

    ButtonController::setSmallButtonPressed(!ButtonController::wasSmallButtonPressed());
}

ISR(INT1_vect) {
    _delay_ms(ButtonController::getDebounceTime());

    ButtonController::setBreadButtonPressed(!ButtonController::wasBreadButtonPressed());
}

bool ButtonController::breadButtonWasPressed_ = false;
bool ButtonController::smallButtonWasPressed_ = false;

void ButtonController::init() {
    cli();

    DDRD &= ~((1 << DDD2) | (1 << DDD3));
    EIMSK |= (1 << INT0) | (1 << INT1);

    EICRA |= (1 << ISC00) | (1 << ISC10);

    sei();
}

bool ButtonController::wasBreadButtonPressed() {
    return breadButtonWasPressed_;
}

bool ButtonController::wasSmallButtonPressed() {
    return smallButtonWasPressed_;
}

void ButtonController::setBreadButtonPressed(bool pressed) {
    breadButtonWasPressed_ = pressed;
}

void ButtonController::setSmallButtonPressed(bool pressed) {
    smallButtonWasPressed_ = pressed;
}

uint8_t ButtonController::getDebounceTime() {
    return DEBOUNCE_TIME;
}
