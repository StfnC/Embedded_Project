#include <avr/io.h>
#include <counter.h>
#include <debug.h>
#include <memoire_24.h>
#include <debug.h>
#include <MotorsController.h>

Memoire24CXXX memoire();
ISR(TIMER1_COMPA_vect) {

}

void writeSpeed() {
    uint8_t leftSpeed = MotorsController::getLeftPercentage();
    
}

int main() {
    DEBUG_INIT;
    CounterInterrupt counter = CounterInterrupt();
    MotorsController::initialization();
    counter.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter.setCompareMode(CompareMode::Toggle);
    counter.setDuration(0.02);


}


