/**
Program implementing a finite state machine following the following diagram.
 \file   pb1.cpp
 \author Rakotoarivony Faneva #2131367 and Lina Belloui #...
 \date   february 14 2022
Created february 21 2022

PIN B OUT (B0 et B1 : DEL)
PIN D IN  (D2 : BUTTONS)
**/

// +────────────────+──────────────────────────────────+──────────────+────────────────────+
// | Present State  | Action                           | NextState    | Output             |
// +────────────────+──────────────────────────────────+──────────────+────────────────────+
// | INIT           | Counter < 120 or Button pressed  | GREEN_BLINK  | OFF                |
// | GREEN_BLINK    | Timer of 1/2 second              | NOTHING      | BLINKING IN GREEN  |
// | NOTHING        | Timer of 2 seconds               | RED_BLINK    | OFF                |
// | RED_BLINK      | Iterate counter / 2 times        | GREEN        | BLINKING IN RED    |
// | GREEN          | Timer 1 second                   | INIT         | Green              |
// +────────────────+──────────────────────────────────+──────────────+────────────────────+

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define F_CPU 8000000
#include <util/delay.h>

enum class State
{
    INIT,
    GREEN_BLINK,
    NOTHING,
    RED_BLINKING,
    GREEN
};

volatile int rButton = 0;
volatile uint8_t counter = 0x00;
volatile uint8_t expiredTimer = 0;

const uint8_t MAX_COUNTER = 120;
const uint16_t DURATION_ONE_SECOND = 7812;
const uint16_t DURATION_HALF_SECOND = 2604;
const uint16_t DURATION_TENTH_SECOND = 781;
const uint16_t DURATION_TWO_SECOND = 15624;

const uint8_t RED = _BV(1);
const uint8_t GREEN = _BV(0);
const uint8_t OFF = 0x00;

void setColor(uint8_t color)
{
    PORTB = color;
}

void startTimer(uint16_t durationSec)
{
    TCNT1 = 0x0;

    OCR1A = durationSec;

    TCCR1A = _BV(COM1A0);

    TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

    TCCR1C = 0;

    TIMSK1 = _BV(OCIE1A);

    expiredTimer = 0;
}

void initialisationUART(void)
{
    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0B |= _BV(TXEN0) | _BV(RXEN0);

    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void initialisation(void)
{

    cli();
    DDRB = _BV(PORTB0) | _BV(PORTB1);
    DDRD = 0x0;

    EIMSK |= _BV(INT0);

    EICRA = _BV(ISC00);

    sei();
}

ISR(TIMER1_COMPA_vect)
{
    counter++;
    expiredTimer = 1;
}

ISR(INT0_vect)
{
    _delay_ms(30);
    rButton = !rButton;
}

uint8_t initState(State &stateMachine)
{
    setColor(OFF);
    uint8_t counterValue = 0;
    if (rButton)
    {
        startTimer(DURATION_TENTH_SECOND);

        while (rButton && counter < MAX_COUNTER)
            ;
        counterValue = counter;
        stateMachine = State::GREEN_BLINK;
    }
    return counterValue;
}

void greenBlinkState(State &stateMachine)
{
    startTimer(DURATION_HALF_SECOND);
    while (!expiredTimer)
    {
        setColor(GREEN);
        _delay_ms(1);
        setColor(OFF);
        _delay_ms(1);
    }
    stateMachine = State::NOTHING;
}

void nothingState(State &stateMachine)
{
    startTimer(DURATION_TWO_SECOND);
    while (!expiredTimer)
        ;
    stateMachine = State::RED_BLINKING;
}

void redBlinkState(State &stateMachine, uint8_t counterValue)
{
    for (uint8_t i = 0; i < counterValue / 2; i++)
    {
        // FIXME : Delete later
        setColor(RED);
        _delay_ms(250);
        setColor(OFF);
        _delay_ms(250);
    }
    stateMachine = State::GREEN;
}

void greenState(State &stateMachine)
{
    setColor(GREEN);
    startTimer(DURATION_ONE_SECOND);
    while (!expiredTimer)
        ;
    stateMachine = State::INIT;
}

int main()
{
    initialisation();

    State stateMachine = State::INIT;
    uint8_t counterValue = 0;

    while (true)
    {

        switch (stateMachine)
        {
        case State::INIT:
            counterValue = initState(stateMachine);
            break;

        case State::GREEN_BLINK:
            greenBlinkState(stateMachine);
            break;

        case State::NOTHING:
            nothingState(stateMachine);
            break;

        case State::RED_BLINKING:
            redBlinkState(stateMachine, counterValue);
            break;

        case State::GREEN:
            greenState(stateMachine);
            break;
        }
    }
}