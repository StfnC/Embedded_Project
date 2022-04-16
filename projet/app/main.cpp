#include <debug.h>
#include <usart.h>

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