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
#define DEBUG_PRINT_MESSAGE_WITH_VALUE(message, value) Debug::printMessage(message, value)
#define DEBUG_PRINT_MESSAGE(message) Debug::printMessage(message)
#define DEBUG_PRINT_VARIABLE(variable) Debug::printVariable(variable)

#else
#define DEBUG_INIT do {} while(0)
#define DEBUG_PRINT_MESSAGE_WITH_VALUE(message, length) do {} while(0)
#define DEBUG_PRINT_MESSAGE(message) do {} while(0)
#define DEBUG_PRINT_VARIABLE(variable) do {} while(0)
#endif

class Debug
{
    public:
        void static initDebug();
        void static printVariable(uint8_t variable);
        void static printMessage(const char message[], uint8_t value);
        void static printMessage(const char message[]);
};