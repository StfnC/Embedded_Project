#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <MotorsController.h>

// FIXME: Write headers for all files, don't forget the pinout

int main() {
    MotorsController motors;

    motors.adjustRightMotorSpeed(10);
    _delay_ms(2000);
    motors.adjustRightMotorSpeed(50);
    _delay_ms(2000);
    motors.adjustRightMotorSpeed(80);
    _delay_ms(2000);
    motors.adjustRightMotorSpeed(100);
    _delay_ms(2000);
    motors.adjustRightMotorSpeed(0);
    _delay_ms(2000);
    motors.adjustLeftMotorSpeed(10);
    _delay_ms(2000);
    motors.adjustLeftMotorSpeed(50);
    _delay_ms(2000);
    motors.adjustLeftMotorSpeed(80);
    _delay_ms(2000);
    motors.adjustLeftMotorSpeed(100);
    _delay_ms(2000);
    motors.adjustLeftMotorSpeed(0);

    return 0;
}