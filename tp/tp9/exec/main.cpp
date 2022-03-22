#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <BuzzerController.h>

int main() {
    BuzzerController::initBuzzer();
    BuzzerController::playNote(45);
    while (true) {
    }
    
    return 0;
};
