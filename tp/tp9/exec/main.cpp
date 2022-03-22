#define F_CPU 8000000

#include <BuzzerController.h>
#include <RobotProgramDownloader.h>
#include <avr/io.h>
#include <Interpreter.h>
#include <util/delay.h>

#include "Partition.h"

int main() {
    DDRA |= (1 << DDA0) | (1 << DDA1);
    BuzzerController::initBuzzer();
    Interpreter interpreter;
    interpreter.interpretCode();
    return 0;
};
