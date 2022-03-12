#include <util/delay.h>
#include "led.h"

led::led(volatile uint8_t* port, uint8_t pin1, uint8_t pin2) : port_(port), pin1_(pin1), pin2_(pin2)
{
}

void led::setGreen()
{
    *port_ |= (1 << pin1_);
    *port_ &= ~(1 << pin2_);
}

void led::setRed()
{
    *port_ &= ~(1 << pin1_);
    *port_ |= (1 << pin2_);
}

void led::setOff()
{
    *port_ &= ~((1 << pin2_) | (1 << pin1_));
}

void led::setYellow() 
{
    setOff();
    while (true) {
        setGreen();
        _delay_ms(5);
        setRed();
        _delay_ms(5);
    }
}