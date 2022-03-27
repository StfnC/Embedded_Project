#include <usart.h>

int main() {
    usart usart;

    while (true) {
        usart.transmitTextMessage("Hello %d world\n", 255);
    }
    
    return 0;
}