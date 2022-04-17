#pragma once

#include <avr/io.h>

class ButtonController {
    public:
        static void init();
        static bool wasBreadButtonPressed();
        static bool wasSmallButtonPressed();
        static void setBreadButtonPressed(bool pressed);
        static void setSmallButtonPressed(bool pressed);
        static uint8_t getDebounceTime();

    private:
        static const uint8_t DEBOUNCE_TIME = 10;
        static bool breadButtonWasPressed_;
        static bool smallButtonWasPressed_;
};
