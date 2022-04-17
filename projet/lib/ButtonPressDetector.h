#pragma once

#include <avr/io.h>

class ButtonPressDetector {
    public:
        static void init();
        static inline constexpr void reset() {
            breadButtonWasPressed_ = false;
            smallButtonWasPressed_ = false;
        }
        static bool wasBreadButtonPressed();
        static bool wasSmallButtonPressed();
        static void setBreadButtonPressed(bool pressed);
        static void setSmallButtonPressed(bool pressed);
        static inline uint8_t getDebounceTime() {
            return DEBOUNCE_TIME;
        }

    private:
        static const uint8_t DEBOUNCE_TIME = 10;
        static bool breadButtonWasPressed_;
        static bool smallButtonWasPressed_;
};
