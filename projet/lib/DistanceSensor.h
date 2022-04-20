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
