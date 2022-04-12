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
uint16_t LightController::average_ = 0;
uint8_t LightController::middleValue_ = 0;
led LightController::led0(&PORTA, DDA2, DDA3);
can LightController::converter_ = can();
uint8_t LightController::highestAmbientValue_;
uint8_t LightController::lowestAmbientValue_;

inline uint8_t max(uint8_t lhs, uint8_t rhs) { return (lhs > rhs) ? lhs : rhs; }
inline uint8_t min(uint8_t lhs, uint8_t rhs) { return (lhs < rhs) ? lhs : rhs; }

void LightController::initialization() {
    DDRA |= ~(_BV(DDA1) | _BV(DDA0));
    DDRA |= _BV(DDA2) | _BV(DDA3);
    usart::initialization();
    middleValue_ = 0;
    averageLightCalculation();
    usart::transmitTextMessage("Luminosite ambiante : %d", average_);
    usart::transmitTextMessage("\tLuminosite ambiante minimale : %d", lowestAmbientValue_);
    usart::transmitTextMessage("\tLuminosite ambiante maximale : %d\n", highestAmbientValue_);
    MotorsController::initialization();
}

void LightController::averageLightCalculation() {
    average_ = 0;
    highestAmbientValue_ = 0;
    lowestAmbientValue_ = UINT8_MAX;
    for (uint16_t i = 0; i < INT16_MAX; i++) {
        leftValue_ = readValue(DDA0);
        rightValue_ = readValue(DDA1);
        average_ += (leftValue_ + rightValue_) / 2;
        if (leftValue_ > highestAmbientValue_ || rightValue_ > highestAmbientValue_) {
            highestAmbientValue_ = (leftValue_ > rightValue_) ? leftValue_ : rightValue_;
        }
        if (leftValue_ < lowestAmbientValue_ || rightValue_ < lowestAmbientValue_) {
            lowestAmbientValue_ = (leftValue_ < rightValue_) ? leftValue_ : rightValue_;
        }
        if (i > 1) {
            average_ = average_ / 2;
        }
    }
}

void LightController::followLight() {
    leftValue_ = readValue(DDA0);
    usart::transmitTextMessage("Gauche : %d", leftValue_);
    rightValue_ = readValue(DDA1);
    usart::transmitTextMessage("\tDroite : %d", rightValue_);
    middleValue_ = leftValue_ - rightValue_ + MIDDLE_VALUE;
    usart::transmitTextMessage("\tMiddle : %d", middleValue_);
    if (leftValue_ > highestAmbientValue_ || rightValue_ > highestAmbientValue_) {
        middleLight();
    }
    else {
        MotorsController::setLeftPercentage(0);
        MotorsController::setRightPercentage(0);
    }
    usart::transmitTextMessage("\n");
}

void LightController::farLeftLight() {
    MotorsController::setLeftPercentage(60);
    MotorsController::setRightPercentage(60);
    MotorsController::changeLeftDirection(Direction::Reverse);
    MotorsController::changeRightDirection(Direction::Forward);
}

void LightController::middleLight() {
    const double scaling = static_cast<double>(UINT8_MAX)/ (UINT8_MAX - highestAmbientValue_);
    uint8_t ocrLeft = (max(leftValue_, highestAmbientValue_) - highestAmbientValue_) * scaling ;
    uint8_t ocrRight =(max(rightValue_, highestAmbientValue_) - highestAmbientValue_) * scaling;


    usart::transmitTextMessage("\t ocrL: %d  ", ocrLeft);
    usart::transmitTextMessage("ocrR: %d", ocrRight);
    if (ocrLeft <= 5) {
        MotorsController::changeRightDirection(Direction::Reverse);
        MotorsController::changeLeftDirection(Direction::Forward);
        MotorsController::setRightPercentage(50);
        MotorsController::setLeftPercentage(50);
    }
    else if (ocrRight <= 5) {
        MotorsController::changeRightDirection(Direction::Forward); 
        MotorsController::changeLeftDirection(Direction::Reverse);
        MotorsController::setLeftPercentage(50);
        MotorsController::setRightPower(50);
    }
    else {
        MotorsController::changeLeftDirection(Direction::Forward);
        MotorsController::changeRightDirection(Direction::Forward);
        MotorsController::setLeftPower(min(ocrRight, 255 - 50) + 50);
        MotorsController::setRightPower(min(ocrLeft, 255 - 50) + 50);
    }
}

void LightController::farRightLight() {
    MotorsController::setLeftPercentage(60);
    MotorsController::setRightPercentage(60);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Reverse);
}

uint8_t LightController::readValue(uint8_t port) {
    return static_cast<uint8_t>(converter_.lecture(port) >> 2);
}