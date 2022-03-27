/**
 * Implementation of the Debug methods
 *
 * \file debug.cpp
 * \author Faneva Rakotoarivony and Stefan Cotargasanu
 * \date March 13 2022
 *
 */

#include "debug.h"

usart Debug::transmitter_;

void Debug::initDebug() {
    transmitter_ = usart();
}

void Debug::printVariable(uint8_t variable) {
    transmitter_.transmit(variable);
}

void Debug::printMessage(const char message[], uint8_t value) {
    transmitter_.transmitTextMessage(message, value);
}

void Debug::printMessage(const char message[]) {
    transmitter_.transmitTextMessage(message);
}
