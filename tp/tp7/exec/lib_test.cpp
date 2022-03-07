#include <avr/io.h>
#include <usart_communication.h>

int main() {
    UsartInitialization();

    while (true) {
        UsartTransmission(0xFF);
    }
    
    return 0;
}