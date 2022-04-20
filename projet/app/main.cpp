/**
 * Final Project Execution
 * 
 * Initializes the Robot and the usart object, then executes the run method of the Robot, which is a state machine
 * 
 * \file main.cpp
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 *      DistanceSensor:
 *          -A2
 *      Photoresistors:
 *          -A4 (Left)
 *          -A5 (Right)
 *      Motherboard Button:
 *          -D2
 *      Breadboard Button:
 *          -D3
 *  Output:
 *      LED:
 *          -A0 (Plug to negative lead)
 *          -A1 (Plug to positive lead)
 *      Motors:
 *          -B3 (Right PWM)
 *          -B5 (Right Direction)
 *          -B4 (Left PWM)
 *          -B7 (Left Direction)
 *      Buzzer:
 *          -D4 (Negative lead)
 *          -D5 (Positive Lead)
 * 
 */

#define F_CPU 8000000L

#include <debug.h>
#include <usart.h>
#include <avr/interrupt.h>

#include "Robot.h"

ISR(TIMER2_COMPA_vect) {
    SystemTimer::incrementTimer();
}

int main() {
    DEBUG_INIT;
    usart::initialization();
    Robot::init();

    while (true) {
        Robot::run();
    }

    return 0;
}