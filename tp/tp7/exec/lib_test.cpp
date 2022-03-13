#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <debug.h>

int main() {

    uint8_t msg[] = "Hello Debug!\n";
    uint8_t msgLength = 14;
    DEBUG_INIT;

    while (true) {
        DEBUG_PRINT_MESSAGE(msg, msgLength);
    }
    
    return 0;
}