/**
 * Implementation of the ButtonInterrupt methods
 * 
 * \file interruptions.cpp
 * \author Faneva Rakotoarivony
 * \date March 13 2022
 *
 * Pins:
 *  Input:
 *      -B2
 *      -D2
 *      -D3
 * 
 *  Output:
 *      -
 * 
 */

#include "interruptions.h"

ButtonInterrupt::ButtonInterrupt(uint8_t interruptNumber, InterruptMode mode) {
    cli();

    // Sets interrupt number
    EIMSK |= _BV(interruptNumber);

    // Sets the mode referring to the Atmel documentation (p. 68)
    switch (mode) {
        case InterruptMode::LowLevelInterrupt:

            EICRA &= ~(_BV(ISC00) << (2 * interruptNumber) | _BV(ISC01) << (2 * interruptNumber));
            break;

        case InterruptMode::AnyEdgeInterrupt:
            EICRA &= ~(_BV(ISC01) << (2 * interruptNumber));
            EICRA |= (_BV(ISC00) << (2 * interruptNumber));
            break;

        case InterruptMode::FallingEdgeInterrupt:
            EICRA &= ~(_BV(ISC00) << (2 * interruptNumber));
            EICRA |= (_BV(ISC01) << (2 * interruptNumber));
            break;

        case InterruptMode::RisingEdgeInterrupt:
            EICRA |= _BV(ISC00) | _BV(ISC01);
            break;
    }

    sei();
}