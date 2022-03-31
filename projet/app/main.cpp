#include <debug.h>
#include <usart.h>

int main() {
    DEBUG_INIT;
    usart::initialization();

    while (true) {
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Hello Debug %d\n", 55);
        DEBUG_PRINT_MESSAGE("Hello Debug Message\n");
        usart::transmitTextMessage("Hello usart\n");
    }
    
    return 0;
}