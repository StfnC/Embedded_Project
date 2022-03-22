#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <interpreter.h>
#include <BuzzerController.h>
#include "Partition.h"

#include "RobotProgramDownloader.h"

int main() {
    // RobotProgramDownloader downloader;
    // downloader.acceptProgramData();

    BuzzerController::initBuzzer();
    Interpreter interpreter;
    interpreter.interpretCode();
    return 0;
};
