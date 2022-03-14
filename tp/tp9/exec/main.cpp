#define F_CPU 8000000

#include <led.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>

#include "RobotProgramDownloader.h"

int main() {
    Memoire24CXXX memory;
    usart usart;
    RobotProgramDownloader program;
    uint8_t dataBuffer;

    program.acceptProgramData();

    _delay_ms(5000);

    memory.lecture(0x0000, &dataBuffer);
    usart.transmit(dataBuffer);
    memory.lecture(0x0000 + sizeof(uint8_t), &dataBuffer);
    usart.transmit(dataBuffer);

    return 0;
}