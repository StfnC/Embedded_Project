#define F_CPU 8000000L

#include <avr/interrupt.h>
#include <debug.h>
#include <SystemTimer.h>
#include <led.h>
#include <util/delay.h>

ISR(TIMER2_COMPA_vect) {
    SystemTimer::incrementTimer();
}

int main() {
    DEBUG_INIT;
    led led(DDA0, DDA1);
    SystemTimer::init();
    SystemTimer::start();

    while (true) {
        if (SystemTimer::getTimer() % 2000 == 0) {
            led.setGreen();
        } else if (SystemTimer::getTimer() % 2000 == 1000) {
            led.setRed();
        }
    }

    return 0;
}