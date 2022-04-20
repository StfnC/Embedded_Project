/**
 * Implementation of the lightController methods
 *
 * \file MotorsController.cpp
 * \author Faneva rakotoarivony
 * \date April 6 2022
 *
 * Pins:
 *  Input:
 *      -A1
 *      -A3
 *
 *  Output:
 *      -
 *
 */
#include "LightController.h"

uint8_t LightController::leftValue_ = 0;
uint8_t LightController::rightValue_ = 0;
uint8_t LightController::middleValue_ = 0;
can LightController::converter_ = can();
uint8_t LightController::highestAmbientValue_;
uint8_t LightController::ocrLeft_ = 0;
uint8_t LightController::ocrRight_ = 0;

inline uint8_t max(uint8_t lhs, uint8_t rhs) { return (lhs > rhs) ? lhs : rhs; }
inline uint8_t min(uint8_t lhs, uint8_t rhs) { return (lhs < rhs) ? lhs : rhs; }

void LightController::initialization() {
    DDRA &= ~(_BV(DDA5) | _BV(DDA4));
    middleValue_ = 0;
    averageLightCalculation();
}

void LightController::averageLightCalculation() {
    highestAmbientValue_ = 0;
    for (uint16_t i = 0; i < INT16_MAX; i++) {
        leftValue_ = readValue(DDA4);
        rightValue_ = readValue(DDA5);
        if (leftValue_ > highestAmbientValue_ || rightValue_ > highestAmbientValue_) {
            highestAmbientValue_ = (leftValue_ > rightValue_) ? leftValue_ : rightValue_;
        }
    }
}

void LightController::followLight() {
    leftValue_ = readValue(DDA4);
    rightValue_ = readValue(DDA5);
    middleValue_ = leftValue_ - rightValue_ + MIDDLE_VALUE;

    if (leftValue_ > highestAmbientValue_ || rightValue_ > highestAmbientValue_) {
        
        const double scaling = static_cast<double>(UINT8_MAX) / (UINT8_MAX - highestAmbientValue_);
        ocrLeft_ = (max(leftValue_, highestAmbientValue_) - highestAmbientValue_) * scaling;
        ocrRight_ = (max(rightValue_, highestAmbientValue_) - highestAmbientValue_) * scaling;

        if (ocrLeft_ <= OCR_PRECISION) {
            noLightLeft();
        }
        else if (ocrRight_ <= OCR_PRECISION) {
            noLightRight();
        }
        else {
            middleLight();
        }
    }
    else {
        MotorsController::setLeftPercentage(0);
        MotorsController::setRightPercentage(0);
    }
}

void LightController::noLightLeft() {
    MotorsController::changeRightDirection(Direction::Reverse);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::setRightPercentage(DEFAULT_SPEED);
    MotorsController::setLeftPercentage(DEFAULT_SPEED);
}

void LightController::middleLight() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPower(min(ocrRight_, UINT8_MAX - DEFAULT_SPEED) + DEFAULT_SPEED);
    MotorsController::setRightPower(min(ocrLeft_, UINT8_MAX - DEFAULT_SPEED) + DEFAULT_SPEED);
}


void LightController::noLightRight() {
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::changeLeftDirection(Direction::Reverse);
    MotorsController::setLeftPercentage(DEFAULT_SPEED);
    MotorsController::setRightPercentage(DEFAULT_SPEED);
}

uint8_t LightController::readValue(uint8_t port) {
    return static_cast<uint8_t>(converter_.lecture(port) >> PRECISION_CAN);
}