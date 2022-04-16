#include <avr/io.h>
#include <LightController.h>
#include <usart.h>

int main() {
    usart::initialization();
    LightController::initialization();

    while (true) {
        LightController::followLight();
    }
}