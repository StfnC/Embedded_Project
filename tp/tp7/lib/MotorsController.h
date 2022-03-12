#include <avr/io.h>
#include <avr/interrupt.h>

class MotorsController {
    public:
        MotorsController();
        ~MotorsController() = default;

        void setLeftPercentage(uint8_t percentage);
        void setRightPercentage(uint8_t percentage);

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
