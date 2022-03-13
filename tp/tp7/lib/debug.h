#include "usart.h"

#ifdef DEBUG
#define DEBUG_INIT Debug()
#define DEBUG_PRINT_MESSAGE(message, length) Debug::printMessage(message, length)
#define DEBUG_COMPARE_SIGNAL(port, pin, value) Debug::compareSignal(port, pin, value)
#define DEBUG_PRINT_VARIABLE(variable) Debug::printVariable(message);

#else
#define DEBUG_INIT do {} while(0)
#define DEBUG_PRINT(message, length) do {} while(0)
#define DEBUG_COMPARE_SIGNAL(port, pin, value) do {} while(0)
#define DEBUG_PRINT_VARIABLE(variable) do {} while(0)
#endif

class Debug
{
    Debug();
    ~Debug();

    void printPortValue(uint8_t port);
    void compareSignal(uint8_t port, uint8_t pin, uint8_t value);
    void printVariable(uint8_t variable);
    void printMessage(uint8_t message[], uint8_t length);
};