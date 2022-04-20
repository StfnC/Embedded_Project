#define F_CPU 8000000L

#include <debug.h>
#include <usart.h>

int main() {
    DEBUG_INIT;
    usart::initialization();

    while (true) {
        usart::transmitTextMessage("Hello Music\n");
    }

    return 0;
}