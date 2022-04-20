#define F_CPU 8000000L

#include <debug.h>
#include <usart.h>
#include <avr/interrupt.h>
#include <SystemTimer.h>
#include <RerunManager.h>

#include "Robot.h"

ISR(TIMER2_COMPA_vect) {
    SystemTimer::incrementTimer();
}

int main() {
    DEBUG_INIT;
    SystemTimer::init();
    SystemTimer::start();
    usart::initialization();
    Robot::init();
    RerunManager::initialization();

    while (true) {
        Robot::run();
        RerunManager::manageRerun();
    }

    return 0;
}