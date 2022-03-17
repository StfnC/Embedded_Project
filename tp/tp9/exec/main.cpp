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

    usart.transmit(0xAA);

    memory.lecture(0x0000, &dataBuffer);
    usart.transmit(dataBuffer);

    memory.lecture(0x0000 + sizeof(uint8_t), &dataBuffer);
    usart.transmit(dataBuffer);

    return 0;
}