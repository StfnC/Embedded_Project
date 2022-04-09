#include <avr/io.h>
#include <LightController.h>
#include <usart.h>
#include <debug.h>

int main() {
    DEBUG_INIT;
    usart::initialization();
    LightController::initialization();

    while (true) {
        LightController::followLight();
    }
}