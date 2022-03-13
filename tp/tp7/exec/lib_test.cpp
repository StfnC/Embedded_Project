/**
 * Testing of the library
 * 
 * \file lib_test.cpp
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date March 13 2022
 *
 */

#define F_CPU 8000000

#include <MotorsController.h>
#include <avr/io.h>
#include <led.h>
#include <util/delay.h>

int main() {
    DDRA |= (1 << DDA0) | (1 << DDA1);

    led del0(&PORTA, DDA0, DDA1);

    MotorsController motors;

    motors.setRightPercentage(50);
    motors.setLeftPercentage(50);
    del0.setGreen();
    _delay_ms(2000);
    motors.changeRightDirection();
    motors.changeLeftDirection();
    del0.setRed();
    _delay_ms(2000);
    motors.changeRightDirection();
    motors.changeLeftDirection();
    del0.setAmber();
    _delay_ms(2000);
    motors.setRightPercentage(0);
    motors.setLeftPercentage(0);
    del0.setOff();

    return 0;
}