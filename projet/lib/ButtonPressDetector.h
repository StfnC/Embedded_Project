#pragma once

#include <avr/io.h>

class ButtonPressDetector {
    public:
        static void init();

        static bool isBreadButtonPressed();
        static bool isSmallButtonPressed();

    private:
        static const uint8_t DEBOUNCE_TIME = 10;
};
