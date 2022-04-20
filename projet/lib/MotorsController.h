/**
 * Definition of the MotorsController class
 * 
 * \file MotorsController.h
 * \author Stefan Cotargasanu
 * \date March 13 2022
 * Output:
 *      -B3
 *      -B4
 *      -B5
 *      -B6
 */


#pragma once
#include <avr/interrupt.h>
#include <avr/io.h>

enum class Direction {
    Forward = 0,
    Reverse = 1
};

class MotorsController {
    public:
        static void initialization();
        static void setLeftPercentage(uint8_t percentage);
        static void setLeftPower(uint8_t value);
        static void changeLeftDirection(Direction direction);
        static void setRightPercentage(uint8_t percentage);
        static void setRightPower(uint8_t value);
        static void changeRightDirection(Direction direction);
        static void invertRightDirection();
        static void invertLeftDirection();

        static uint8_t getLeftPercentage();
        static uint8_t getRightPercentage();
        static bool getLeftDirection();
        static bool getRightDirection();

    private:
        static constexpr uint8_t MAX_TIMER_VALUE = 255;
        static constexpr uint8_t ONE_HUNDRED_PERCENT = 100;

        static Direction directionLeft_; 
        static Direction directionRight_; 
        static uint8_t leftSpeed_;
        static uint8_t rightSpeed_;

        static uint8_t convertPercentageToTimerValue(uint8_t percentage);
        static uint8_t convertTimerValueToPercentage(uint8_t timerValue);
        static void adjustLeftMotorSpeed();
        static void adjustRightMotorSpeed();
};
