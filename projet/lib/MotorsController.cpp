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

uint8_t MotorsController::leftSpeed_ = 0;
uint8_t MotorsController::rightSpeed_ = 0;
Direction MotorsController::directionLeft_ = Direction::Forward;
Direction MotorsController::directionRight_ = Direction::Forward;

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
    if (percentage >= 0 && percentage <= ONE_HUNDRED_PERCENT) {
        leftSpeed_ = convertPercentageToTimerValue(percentage);
        adjustLeftMotorSpeed();
    }
}

void MotorsController::setLeftPower(uint8_t value) {
    if (value >= 0 && value <= UINT8_MAX) {
        leftSpeed_ = value;
        adjustLeftMotorSpeed();
    }
}

void MotorsController::changeLeftDirection(Direction direction) {
    switch (direction) {
    case Direction::Forward:
        directionLeft_ = Direction::Forward;
        PORTB &= ~(1 << DDB6);
        break;
    case Direction::Reverse:
        directionLeft_ = Direction::Reverse;
        PORTB |= (1 << DDB6);
        break;
    }
}

bool MotorsController::getLeftDirection() {
    return static_cast<bool>(directionLeft_);
}

void MotorsController::changeRightDirection(Direction direction) {
    switch (direction) {
    case Direction::Forward:
        directionRight_ = Direction::Forward;
        PORTB &= ~(1 << DDB5);
        break;
    case Direction::Reverse:
        directionRight_ = Direction::Reverse;
        PORTB |= (1 << DDB5);
        break;
    }
}

bool MotorsController::getRightDirection() {
    return static_cast<bool>(directionRight_);
}

void MotorsController::invertRightDirection() {
    PORTB ^= (1 << DDB5);
}

void MotorsController::invertLeftDirection() {
    PORTB ^= (1 << DDB6);
}

void MotorsController::setRightPercentage(uint8_t percentage) {
    if (percentage >= 0 && percentage <= ONE_HUNDRED_PERCENT) {
        rightSpeed_ = convertPercentageToTimerValue(percentage);
        adjustRightMotorSpeed();
    }
}

void MotorsController::setRightPower(uint8_t value) {
    if (value >= 0 && value <= UINT8_MAX) {
        rightSpeed_ = value;
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
    return static_cast<uint8_t>(percentage * MAX_TIMER_VALUE / ONE_HUNDRED_PERCENT);
}

uint8_t MotorsController::convertTimerValueToPercentage(uint8_t timerValue) {
    return static_cast<uint8_t>(timerValue * ONE_HUNDRED_PERCENT / MAX_TIMER_VALUE);
}

void MotorsController::adjustLeftMotorSpeed() {
    OCR0B = leftSpeed_;
}

void MotorsController::adjustRightMotorSpeed() {
    OCR0A = rightSpeed_;
}

