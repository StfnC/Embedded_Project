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
    DDRA |= ~(_BV(DDA1) | _BV(DDA0));
    usart::initialization();
    middleValue_ = 0;
    averageLightCalculation();
    usart::transmitTextMessage("Luminosite ambiante : %d", average_);
    MotorsController::initialization();
}

void LightController::averageLightCalculation() {
    average_ = 0;
    for (uint16_t i = 0; i < 10000; i++) {
        leftValue_ = readValue(DDA0);
        rightValue_ = readValue(DDA1);
        average_ += (leftValue_ + rightValue_) / 2;
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
    if (leftValue_ >= average_ + HIGH_VALUE_LIGHT || rightValue_ >= average_ + HIGH_VALUE_LIGHT) {
        if (middleValue_ <= 70) {
            usart::transmitTextMessage("\t FAR LEFT");
            farLeftLight();
        }
        else if (middleValue_ >= 200) {
            usart::transmitTextMessage("\tFAR RIGHT");
            farRightLight();
        }
        else {
            usart::transmitTextMessage("\tMIDDLE");
            if (leftValue_ > rightValue_ + 2) {
                middleLeft();
            }
            else if (leftValue_ < rightValue_ - 2) {
                middleRight();
            }
            else {
                middleLight();
            }
        }
    }
    else {
        MotorsController::setLeftPercentage(0);
        MotorsController::setRightPercentage(0);
    }
    usart::transmitTextMessage("\n");
}

void LightController::middleRight() {
    uint8_t difference = abs(leftValue_ - rightValue_);
    usart::transmitTextMessage("\tDifference : %d", difference);
    usart::transmitTextMessage("  ocrleft : %d", leftValue_ + 4 * difference);
    usart::transmitTextMessage("  ocrright : %d", rightValue_ - 4 * difference);
    MotorsController::setRightPower(leftValue_ + 2 * difference);
    MotorsController::setLeftPower(rightValue_ - 2 * difference);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
}

void LightController::middleLeft() {
    uint8_t difference = abs(leftValue_ - rightValue_);
    usart::transmitTextMessage("\tDifference : %d", difference);
    usart::transmitTextMessage("  ocrleft : %d", leftValue_ - 4 * difference);
    usart::transmitTextMessage("  ocrright : %d", rightValue_ + 4 * difference);
    MotorsController::setRightPower(leftValue_ - 2 * difference);
    MotorsController::setLeftPower(rightValue_ + 2 * difference);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
}

void LightController::farLeftLight() {
    MotorsController::setLeftPercentage(60);
    MotorsController::setRightPercentage(60);
    MotorsController::changeLeftDirection(Direction::Reverse);
    MotorsController::changeRightDirection(Direction::Forward);
}

void LightController::middleLight() {
    uint8_t difference = abs(leftValue_ - rightValue_);
    usart::transmitTextMessage("\tDifference : %d", difference);
    usart::transmitTextMessage("  ocrleft : %d", leftValue_ + 2 * difference);
    usart::transmitTextMessage("  ocrright : %d", rightValue_ + 2 * difference);
    MotorsController::setLeftPower(leftValue_ + 2 * difference);
    MotorsController::setRightPower(rightValue_ + 2 * difference);
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
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