
#include "del.h"

void del::del(uint8_t port,uint8_t pin1, uint8_t pin2)
{
    port_ = port;
    pin1_ = pin1; //0
    pin2_ = pin2; //1
}

void del::delGreen()
{

    port_ |= (1 << pin2_);
    port_ &= ~(1 << pin1_);

}

void del::delRed()
{

    port_ |= (1 << pin1_);
    port_ &= ~(1 << pin2_);

}

void del::delOff()
{
    port_ &= ~((1 << pin2_) | (1 << pin1_));
}

void del::delYellow() 
{
    delOff();
    while (true) {
        delGreen();
        _delay_ms(5);
        delRed():
        _delay_ms(5);
    }
}