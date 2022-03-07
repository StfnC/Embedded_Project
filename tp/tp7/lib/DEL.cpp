
#include "DEL.h"

void DEL::DEL(uint8_t port,uint8_t pin1, uint8_t pin2)
{
    port_ = port;
    pin1_ = pin1; //0
    pin2_ = pin2; //1
}

void DEL::DEL_GREEN()
{

    port_ |= (1 << pin2_);
    port_ &= ~(1 << pin1_);

}

void DEL::DEL_RED()
{

    port_ |= (1 << pin1_);
    port_ &= ~(1 << pin2_);

}

void DEL::DEL_OFF()
{
    port_ &= ~((1 << pin2_) | (1 << pin1_));
}

void DEL::DEL_YELLOW() 
{
    DEL_OFF();
    while (true) {
        DEL_GREEN();
        _delay_ms(5);
        DEL_RED():
        _delay_ms(5);
    }
}