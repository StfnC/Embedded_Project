#include <avr/io.h>
#include <avr/interrupt.h>

class MotorsController {
    public:
        MotorsController();
        ~MotorsController() = default;

        void setLeftPercentage(uint8_t percentage);
        void setRightPercentage(uint8_t percentage);

    private:
        uint8_t leftSpeed_;
        uint8_t rightSpeed_;

        void initialization();
        uint8_t convertPercentageToTimerValue(uint8_t percentage);
        void adjustLeftMotorSpeed();
        void adjustRightMotorSpeed();
};
