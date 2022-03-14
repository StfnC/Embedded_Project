/**
 * Definition of the MotorsController class
 * 
 * \file MotorsController.h
 * \author Stefan Cotargasanu
 * \date March 13 2022
 * 
 */

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>

class MotorsController {
    public:
        MotorsController();
        ~MotorsController() = default;

        void setLeftPercentage(uint8_t percentage);
        void changeLeftDirection();
        void setRightPercentage(uint8_t percentage);
        void changeRightDirection();

        uint8_t getLeftPercentage();
        uint8_t getRightPercentage();

    private:
        static const uint8_t MAX_TIMER_VALUE = 255;

        uint8_t leftSpeed_;
        uint8_t rightSpeed_;

        void initialization();
        uint8_t convertPercentageToTimerValue(uint8_t percentage);
        uint8_t convertTimerValueToPercentage(uint8_t timerValue);
        void adjustLeftMotorSpeed();
        void adjustRightMotorSpeed();
};
