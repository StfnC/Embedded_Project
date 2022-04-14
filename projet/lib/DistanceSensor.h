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

        static const uint8_t PIN_;
        static can can_;
};
