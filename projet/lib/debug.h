/**
 * Definition of the Debug class and the associated macros
 * 
 * \file debug.h
 * \author Faneva Rakotoarivony and Stefan Cotargasanu
 * \date March 13 2022
 *
 */
#pragma once
#include "usart.h"

#ifdef DEBUG
#define DEBUG_INIT Debug::initDebug()
#define DEBUG_PRINT_MESSAGE(message, length) Debug::printMessage(message, length)
#define DEBUG_COMPARE_SIGNAL(port, pin, value) Debug::compareSignal(port, pin, value)
#define DEBUG_PRINT_VARIABLE(variable) Debug::printVariable(variable)

#else
#define DEBUG_INIT do {} while(0)
#define DEBUG_PRINT_MESSAGE(message, length) do {} while(0)
#define DEBUG_COMPARE_SIGNAL(port, pin, value) do {} while(0)
#define DEBUG_PRINT_VARIABLE(variable) do {} while(0)
#endif

class Debug
{
    public:
        void static initDebug();
        void static printPortValue(uint8_t port);
        void static compareSignal(uint8_t port, uint8_t pin, uint8_t value);
        void static printVariable(uint8_t variable);
        void static printMessage(uint8_t message[], uint8_t length);

    private:
        static usart transmitter_;
};