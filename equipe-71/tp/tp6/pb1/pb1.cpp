/**
 * First problem of the TP6
 * This code implements the state machine described in the first problem of the TP6.
 * First the program will wait for the press of a button.
 * Then a counter that increments every 100ms is started.
 * If the counter reaches COUNTER_MAX_VALUE or the button is released, a green LED will blink for 500ms
 * Then the red LED will blink COUNTER_MAX_VALUE / 2 times.
 * Finally, the led will stay green for a second and then the machine will go back to the initial.
 *
 * \file pb1.cpp
 * \author Stefan Cotargasanu and Justine Sauquet
 * \date February 21 2022
 *
 * Pins:
 *  Input:
 *      -D2
 *  Output:
 *      -B0
 *      -B1
 *
 * Table 1 : States table for the first problem
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | Present State  | Button Input | Timer Input    | Next State         | Output             |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | INIT           | RELEASED     | X              | INIT               | LED_OFF            |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | INIT           | PRESSED      | X              | INIT               | LED_OFF            |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BUTTON_PRESSED | RELEASED     | X < 12 * 100ms | BLINKING_GREEN     | LED_OFF            |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BUTTON_PRESSED | PRESSED      | X < 12 * 100ms | BUTTON_PRESSED     | LED_OFF            |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BUTTON_PRESSED | PRESSED      | 12 * 100ms     | BLINKING_GREEN     | LED_OFF            |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BLINKING_GREEN | -            | X < 500ms      | BLINKING_GREEN     | LED_BLINKING_GREEN |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BLINKING_GREEN | -            | 500ms          | BLINKING_RED       | LED_BLINKING_GREEN |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BLINKING_RED   | -            | X < (counter / 4)s | BLINKING_RED   | LED_BLINKING_RED   |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | BLINKING_RED   | -            | X = (counter / 4)s | LIT_UP_GREEN   | LED_BLINKING_RED   |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | LIT_UP_GREEN   | -            | X < 1000ms     | BLINKING_RED       | LED_GREEN          |
 * +----------------+--------------+----------------+--------------------+--------------------+
 * | LIT_UP_GREEN   | -            | 1000ms         | INIT               | LED_GREEN          |
 * +----------------+--------------+----------------+--------------------+--------------------+
 *
 */

#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "State.hpp"

const uint8_t DEBOUNCE_TIME = 10;
const uint8_t BLINKING_DELAY = 25;
const uint8_t COUNTER_MAX_VALUE = 120;
const uint16_t ONE_SECOND_WITH_1024_PRESCALER = 7812;

volatile bool gButtonPressed = false;
volatile bool gTimerExpired = true;

ISR(TIMER1_COMPA_vect) {
    gTimerExpired = true;
}

ISR(INT0_vect) {
    _delay_ms(DEBOUNCE_TIME);

    gButtonPressed = !gButtonPressed;
}

void initialization() {
    // Configuration based on previous exercices
    cli();

    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRD &= ~(1 << DDD2);

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00);

    sei();
}

void startTimer(uint16_t duration) {
    gTimerExpired = false;

    TCNT1 = 0;

    OCR1A = duration;

    TCCR1A = 0;

    // CTC, Prescaler of 1024
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A);
}

void lightRedLed() {
    PORTB &= ~(1 << DDB0);
    PORTB |= 1 << DDB1;
}

void lightGreenLed() {
    PORTB |= 1 << DDB0;
    PORTB &= ~(1 << DDB1);
}

void turnOffLed() {
    PORTB &= ~(1 << DDB0) & ~(1 << DDB1);
}

void handleInitState(State& state) {
    turnOffLed();
    if (gButtonPressed) {
        state = State::BUTTON_PRESSED;
    }
}

void handleButtonPressedState(State& state, uint8_t& counter) {
    if (gButtonPressed && counter < COUNTER_MAX_VALUE) {
        if (gTimerExpired) {
            startTimer(ONE_SECOND_WITH_1024_PRESCALER / 10);
            counter++;
        }
    } else {
        state = State::BLINKING_GREEN;
    }
}

void handleBlinkingGreenState(State& state) {
    startTimer(ONE_SECOND_WITH_1024_PRESCALER / 2);

    while (!gTimerExpired) {
        lightGreenLed();
        startTimer(ONE_SECOND_WITH_1024_PRESCALER / 10 / 2);
        while (!gTimerExpired) {
        }
        turnOffLed();
        startTimer(ONE_SECOND_WITH_1024_PRESCALER / 10 / 2);
        while (!gTimerExpired) {
        }
    }
    state = State::BLINKING_RED;
}

void handleBlinkingRedState(State& state, uint8_t& counter) {
    for (uint8_t i = 0; i < counter / 2; i++) {
        lightRedLed();
        startTimer(ONE_SECOND_WITH_1024_PRESCALER / 4);
        while (!gTimerExpired) {
        }

        turnOffLed();
        startTimer(ONE_SECOND_WITH_1024_PRESCALER / 4);
        while (!gTimerExpired) {
        }
    }
    counter = 0;
    state = State::LIT_UP_GREEN;
}

void handleLitUpGreenState(State& state) {
    lightGreenLed();
    startTimer(ONE_SECOND_WITH_1024_PRESCALER);
    while (!gTimerExpired) {
    }
    // This fixes a bug where if the user pressed on the button in between states,
    // the state might switch directly to pressed button state after lit up green state
    gButtonPressed = false;

    state = State::INIT;
}

void manageStateMachine(State& state, uint8_t& counter) {
    switch (state) {
        case State::INIT:
            handleInitState(state);
            break;
        case State::BUTTON_PRESSED:
            handleButtonPressedState(state, counter);
            break;
        case State::BLINKING_GREEN:
            handleBlinkingGreenState(state);
            break;
        case State::BLINKING_RED:
            handleBlinkingRedState(state, counter);
            break;
        case State::LIT_UP_GREEN:
            handleLitUpGreenState(state);
            break;
    }
}

int main() {
    initialization();

    State state = State::INIT;
    uint8_t counter = 0;

    while (true) {
        manageStateMachine(state, counter);
    }

    return 0;
}