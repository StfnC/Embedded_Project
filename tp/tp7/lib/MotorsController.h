#include <avr/io.h>
#include <avr/interrupt.h>

class MotorsController {
    public:
        MotorsController();
        ~MotorsController() = default;

        void adjustLeftMotorSpeed(uint8_t percentage);
        void adjustRightMotorSpeed(uint8_t percentage);

    private:
        uint8_t leftSpeed;
        uint8_t rightSpeed;

        void initialization();
        uint8_t convertPercentageToTimerValue(uint8_t percentage);
};
