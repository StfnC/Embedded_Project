#include <debug.h>

int main() {
    DEBUG_INIT;

    while (true) {
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Hello Debug %d\n", 55);
        DEBUG_PRINT_MESSAGE("Hello Debug Message\n");
    }
    
    return 0;
}