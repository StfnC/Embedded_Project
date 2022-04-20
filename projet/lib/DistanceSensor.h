/**
 * Definition of DistanceCensor class methods
 * 
 * \file DistanceSensor.h
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 *      DistanceSensor:
 *          -A2
 * 
 *  Output:
 * 
 */
#pragma once

#include <avr/io.h>
#include "can.h"

class DistanceSensor {
    public:
        static void initialization();
        static uint8_t getDistanceCm();

    private:
        static void calibrate();
        static uint8_t getAnalogReading();


        static constexpr double INTERCEPT = 10.03;
        static constexpr double A_COEFFICENT = 1.6;
        static const uint8_t PIN_ = 2;
        static can can_;
};
