#define F_CPU 8000000

#include <debug.h>
#include <led.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>

#include "RobotProgramDownloader.h"

int main() {
    DEBUG_INIT;
    Memoire24CXXX memory;
    usart usart;
    RobotProgramDownloader program;
    uint8_t dataBuffer = 0x00;

    program.acceptProgramData();

    // _delay_ms(3000);
    usart.transmit(0xAA);

    for (uint16_t i = 0; i < 30; i++) {
        memory.lecture(0x0000 + i * sizeof(uint8_t), &dataBuffer);
        usart.transmit(dataBuffer);
        _delay_ms(5);
    }

    return 0;
}