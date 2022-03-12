#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <MotorsController.h>

// FIXME: Write headers for all files, don't forget the pinout

int main() {
    MotorsController motors;

    motors.setRightPercentage(50);
    motors.setLeftPercentage(50);
    _delay_ms(2000);
    motors.changeRightDirection();
    motors.changeLeftDirection();
    _delay_ms(2000);
    motors.changeRightDirection();
    motors.changeLeftDirection();
    _delay_ms(2000);
    motors.setRightPercentage(0);
    motors.setLeftPercentage(0);

    return 0;
}