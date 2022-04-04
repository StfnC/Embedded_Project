/**
 * Implementation of the Debug methods
 *
 * \file debug.cpp
 * \author Faneva Rakotoarivony and Stefan Cotargasanu
 * \date March 13 2022
 *
 */

#include "debug.h"

void Debug::initDebug() {
    usart::initialization();
}

void Debug::printVariable(uint8_t variable) {
    usart::transmit(variable);
}

void Debug::printMessage(const char message[], uint8_t value) {
    usart::transmitTextMessage(message, value);
}

void Debug::printMessage(const char message[]) {
    usart::transmitTextMessage(message);
}
