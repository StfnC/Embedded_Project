#include "MotorsController.h"

MotorsController::MotorsController() : leftSpeed_(0), rightSpeed_(0) {
    MotorsController::initialization();
}

void MotorsController::initialization() {
    cli();

    // To output on OC0A and OC0B
    DDRB |= (1 << DDB3) | (1 << DDB4);

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

void MotorsController::setRightPercentage(uint8_t percentage) {
    if (percentage >= 0 && percentage <= 100) {
        rightSpeed_ = convertPercentageToTimerValue(percentage);
        adjustRightMotorSpeed();
    }
}

uint8_t MotorsController::convertPercentageToTimerValue(uint8_t percentage) {
    return static_cast<uint8_t>(percentage * 255 / 100);
}

void MotorsController::adjustLeftMotorSpeed() {
    OCR0B = leftSpeed_;
}

void MotorsController::adjustRightMotorSpeed() {
    OCR0A = rightSpeed_;
}
