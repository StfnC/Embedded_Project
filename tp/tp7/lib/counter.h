#include <avr/interrupt.h>

/* Set counter on Timer 1 */

class CounterInterrupt
{
public:
    CounterInterrupt();
    ~CounterInterrupt();

    void setDuration(uint16_t duration);

    void setNormal();
    void setCtc();
    void setOff();


    void setToggle();
    void setToLow();
    void setToHigh();
};
