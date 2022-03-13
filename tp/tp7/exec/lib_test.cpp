#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>

#ifdef DEBUG
#define DEBUG_INIT usart::initialization()
#define DEBUG_PRINT(message, length) usart::transmitTextMessage(message, length)
#else
#define DEBUG_INIT do {} while(0)
#define DEBUG_PRINT(message, length) do {} while(0)
#endif

// FIXME: Write headers for all files, don't forget the pinout

int main() {
    uint8_t msg[] = "Hello Debug!";
    uint8_t msgLength = 13;
    DEBUG_INIT;

    DEBUG_PRINT(msg, msgLength);

    return 0;
}