#include "debug.h"

usart Debug::transmitter_;

void Debug::initDebug()
{
    transmitter_ = usart();
}

void Debug::printPortValue(uint8_t port)
{
    transmitter_.transmit(port);
}

void Debug::compareSignal(uint8_t port, uint8_t pin, uint8_t value)
{
    transmitter_.transmit((port & pin) & value);
}

void Debug::printVariable(uint8_t variable)
{
    transmitter_.transmit(variable);
}

void Debug::printMessage(uint8_t message[], uint8_t length)
{
    transmitter_.transmitTextMessage(message, length);
}