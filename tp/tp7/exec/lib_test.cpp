#include <avr/io.h>
#include <usart.h>

int main() {
    usart usartCommunication;

    while (true) {
        usartCommunication.transmit(0xFF);
    }
    
    return 0;
}