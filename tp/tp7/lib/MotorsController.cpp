#include "MotorsController.h"

MotorsController::MotorsController() {
    MotorsController::initialization();
}

void MotorsController::initialization() {
    cli();

    // To output on OC0A and OC0B
    DDRB |= (1 << DDB3) | (1 << DDB4);

    adjustLeftMotorSpeed(0);

    adjustRightMotorSpeed(0);

    // Mode 1 from p.130 of the Atmel documentation
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);

    // clk / 8
    TCCR0B |= (1 << CS01);

    sei();
}

uint8_t MotorsController::convertPercentageToTimerValue(uint8_t percentage) {
    return static_cast<uint8_t>(percentage * 255 / 100);
}

void MotorsController::adjustLeftMotorSpeed(uint8_t percentage) {
    OCR0B = convertPercentageToTimerValue(percentage);
}

void MotorsController::adjustRightMotorSpeed(uint8_t percentage) {
    OCR0A = convertPercentageToTimerValue(percentage);
}
