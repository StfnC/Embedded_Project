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
can LightController::converter_ = can();


void LightController::initialization() {
    DDRA |= ~(_BV(DDA1) | _BV(DDA3));
    usart::initialization();
    middleValue_ = 0;
    averageLightCalculation();
    usart::transmitTextMessage("Luminosite ambiante : %d", average_);
    MotorsController::initialization();
}

void LightController::averageLightCalculation() {
    average_ = 0;
    for (uint16_t i = 0; i < 10000; i++) {
        leftValue_ = readValue(DDA3);
        rightValue_ = readValue(DDA1);
        average_ += (leftValue_ + rightValue_) / 2;
        if (i > 1) {
            average_ = average_ / 2;
        }
    }
}

void LightController::followLight() {
    leftValue_ = readValue(DDA3);
    usart::transmitTextMessage("Gauche : %d", leftValue_);
    rightValue_ = readValue(DDA1);
    usart::transmitTextMessage("\tDroite : %d", rightValue_);
    if (leftValue_ >= average_ + HIGH_VALUE_LIGHT || rightValue_ >= average_ + HIGH_VALUE_LIGHT) {
        middleValue_ = leftValue_ - rightValue_ + MIDDLE_VALUE;
        usart::transmitTextMessage("\tMiddle : %d", middleValue_);
        if (middleValue_ >= 138) {
            usart::transmitTextMessage("\t FAR LEFT");
            farLeftLight();
        }
        else if (middleValue_ <= 122) {
            usart::transmitTextMessage("\tFAR RIGHT");
            farRightLight();
        }
        else {
            usart::transmitTextMessage("\tMIDDLE");
            middleLight();
        }
    }
    else {
        MotorsController::setLeftPercentage(0);
        MotorsController::setRightPercentage(0);
    }
    usart::transmitTextMessage("\n");
}

void LightController::farLeftLight() {
    MotorsController::setLeftPercentage(90);
    MotorsController::setRightPercentage(90);
    MotorsController::changeLeftDirection(Direction::Reverse);
    MotorsController::changeRightDirection(Direction::Forward);
}

void LightController::middleLight() {
    MotorsController::setLeftPower(rightValue_);
    MotorsController::setRightPower(leftValue_);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
}


void LightController::farRightLight() {
    MotorsController::setLeftPercentage(90);
    MotorsController::setRightPercentage(90);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Reverse);
}

uint8_t LightController::readValue(uint8_t port) {
    return static_cast<uint8_t>(converter_.lecture(port) >> 2);
}