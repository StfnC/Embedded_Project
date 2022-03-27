#include <usart.h>

int main() {
    usart usart;

    while (true) {
        usart.transmitTextMessage("Hello world\n\t");
    }
    
    return 0;
}