#define F_CPU 8000000L

#include <ButtonPressDetector.h>
#include <avr/io.h>
#include <util/delay.h>
#include <led.h>

int main() {
    led led(DDA0, DDA1);
    ButtonPressDetector::init();

    while (true) {
        if (!ButtonPressDetector::wasBreadButtonPressed() && !ButtonPressDetector::wasSmallButtonPressed()) {
            led.setOff();
        } else if (ButtonPressDetector::wasBreadButtonPressed()) {
            led.setGreen();
            _delay_ms(1000);
            ButtonPressDetector::setBreadButtonPressed(false);
        } else {
            led.setRed();
            _delay_ms(1000);
            ButtonPressDetector::setSmallButtonPressed(false);
        }
    }
}