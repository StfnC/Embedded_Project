#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <BuzzerController.h>

int main() {
    BuzzerController::initBuzzer();
    BuzzerController::playNote(0x60);
    BuzzerController::stopNote();
    return 0;
};
