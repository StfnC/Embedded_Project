#include <avr/io.h>
#include <usart.h>

int main() {
    usart::initialization();
    DDRD &= ~(1 << DDD3);

    while (true) {
        uint8_t buttonPressed = PIND & (1 << DDD3);
        usart::transmitTextMessage("Button PIN : %d\n", buttonPressed);
    }
}