#include <avr/io.h>
#include <avr/interrupt.h>

class MotorsController {
    public:
        MotorsController();
        ~MotorsController() = default;

        void adjustLeftMotorSpeed(uint8_t percentage);
        void adjustRightMotorSpeed(uint8_t percentage);

    private:
        uint8_t leftPercentage;
        uint8_t rightPercentage;

        void initialization();
};
