#include <ButtonController.h>
#include <avr/io.h>
#include <led.h>

int main() {
    led led(DDA0, DDA1);
    ButtonController::init();

    while (true) {
        if (!ButtonController::wasBreadButtonPressed() && !ButtonController::wasSmallButtonPressed()) {
            led.setOff();
        } else if (ButtonController::wasBreadButtonPressed()) {
            led.setGreen();
        } else {
            led.setRed();
        }
    }
}