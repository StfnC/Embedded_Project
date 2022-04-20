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

            EICRA &= ~((1 << ISC00) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            EICRA &= ~((1 << ISC01) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            break;

        case InterruptMode::AnyEdgeInterrupt:
            EICRA &= ~((1 << ISC01) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            EICRA |= ((1 << ISC00) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            break;

        case InterruptMode::FallingEdgeInterrupt:
            EICRA &= ~((1 << ISC00) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            EICRA |= ((1 << ISC01) << (INTERRUPT_NUMBER_MULTIPLIER * interruptNumber));
            break;

        case InterruptMode::RisingEdgeInterrupt:
            EICRA |= (1 << ISC00) | (1 << ISC01);
            break;
    }

    sei();
}