#include <avr/interrupt.h>

/* Set counter on Timer 1 */

class CounterInterrupt
{
public:
    CounterInterrupt();
    ~CounterInterrupt();

    void setDuration(uint8_t duration);

    void setNormal();
    void setCtc();
    void setToggle();
    void setToLow();
    void setToHigh();
    void setOff();
};
