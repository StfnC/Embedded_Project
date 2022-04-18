#define F_CPU 8000000L

#include <debug.h>
#include <usart.h>
#include <avr/interrupt.h>

#include "Robot.h"



int main() {
    DEBUG_INIT;
    usart::initialization();
    Robot::init();

    while (true) {
        Robot::run();
    }

    return 0;
}