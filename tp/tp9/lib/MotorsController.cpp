/**
 * Implementation of the MotorsController methods
 * 
 * \file MotorsController.cpp
 * \author Stefan Cotargasanu
 * \date March 13 2022
 *
 * Pins:
 *  Input:
 *      -
 * 
 *  Output:
 *      -B3
 *      -B4
 *      -B5
 *      -B6
 * 
 */

#include "MotorsController.h"

MotorsController::MotorsController() : leftSpeed_(0), rightSpeed_(0) {
    MotorsController::initialization();
}

void MotorsController::initialization() {
    cli();

    // To output on OC0A and OC0B and for the direction
    DDRB |= (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6);

    // Mode 1 from p.130 of the Atmel documentation
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);

    // clk / 8
    TCCR0B |= (1 << CS01);

    sei();
}

void MotorsController::setLeftPercentage(uint8_t percentage) {
    if (percentage >= 0 && percentage <= 100) {
        leftSpeed_ = convertPercentageToTimerValue(percentage);
        adjustLeftMotorSpeed();
    }
}

void MotorsController::changeLeftDirection() {
    PORTB ^= (1 << DDB6);
}

void MotorsController::changeRightDirection() {
    PORTB ^= (1 << DDB5);
}

void MotorsController::setRightPercentage(uint8_t percentage) {
    if (percentage >= 0 && percentage <= 100) {
        rightSpeed_ = convertPercentageToTimerValue(percentage);
        adjustRightMotorSpeed();
    }
}

uint8_t MotorsController::getLeftPercentage() {
    return convertTimerValueToPercentage(leftSpeed_);
}

uint8_t MotorsController::getRightPercentage() {
    return convertTimerValueToPercentage(rightSpeed_);
}

uint8_t MotorsController::convertPercentageToTimerValue(uint8_t percentage) {
    return static_cast<uint8_t>(percentage * MAX_TIMER_VALUE / 100);
}

uint8_t MotorsController::convertTimerValueToPercentage(uint8_t timerValue) {
    return static_cast<uint8_t>(timerValue * 100 / MAX_TIMER_VALUE);
}

void MotorsController::adjustLeftMotorSpeed() {
    OCR0B = leftSpeed_;
}

void MotorsController::adjustRightMotorSpeed() {
    OCR0A = rightSpeed_;
}
