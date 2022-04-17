#include <ButtonController.h>
#include <avr/io.h>
#include <usart.h>

int main() {
    usart::initialization();
    ButtonController::init();

    while (true) {
        uint8_t buttonPressed = PIND & (1 << DDD3);
        usart::transmitTextMessage("Button BREAD : %d\n", ButtonController::wasBreadButtonPressed());
        usart::transmitTextMessage("Button SMALL : %d\n", ButtonController::wasSmallButtonPressed());
    }
}