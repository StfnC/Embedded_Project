#include "debug.h"

Debug::Debug()
{
    usart::initialization();
}

void Debug::printPortValue(uint8_t port)
{
    usart::transmit(port);
}

void Debug::compareSignal(uint8_t port, uint8_t pin, uint8_t value)
{
    usart::transmit((port & pin) & value);
}

void Debug::printVariable(uint8_t variable)
{
    usart::transmit(variable);
}

void Debug::printMessage(uint8_t message[], uint8_t length)
{
    usart::transmitTextMessage(message, length);
}