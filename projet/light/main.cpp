#include <avr/io.h>
#include <MotorsController.h>
#include <LightController.h>
#include <usart.h>

int main() {
    usart::initialization();
    MotorsController::initialization();
    LightController::initialization();

    while (true) {
        LightController::followLight();
    }
}