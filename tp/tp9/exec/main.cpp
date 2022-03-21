#define F_CPU 8000000

#include <debug.h>
#include <interpreter.h>
#include <led.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>

#include "RobotProgramDownloader.h"

int main() {
    DEBUG_INIT;

    DDRA |= (1 << DDA0) | (1 << DDA1);

    // RobotProgramDownloader programmer;

    // programmer.acceptProgramData();

    Interpreter interpreter;
    uint8_t nInstructions = interpreter.getNumberInstructions();

    for (uint16_t i = 0; i < nInstructions; i++) {
        interpreter.interpretLine();
    }

    return 0;
}