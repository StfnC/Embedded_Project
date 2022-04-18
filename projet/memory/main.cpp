#define F_CPU 8000000
#include <memoire_24.h>
#include <LightController.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <counter.h>
#include <usart.h>
#include <RerunManager.h>
#include <MotorsController.h>
volatile bool gMinuterieExpiree = false;
volatile int valeurAvantInterruption;
volatile int valeurApresInterruption;
volatile int counter = 0;

ISR(TIMER2_COMPA_vect) {
    RerunManager::manageRerun();
}

void wipeMemory() {
    Memoire24CXXX memory;

    for (uint16_t i = 0; i < UINT16_MAX; i++) {
        memory.ecriture(i, 0);
        _delay_ms(3);
    }
}


int main() {
    // wipeMemory();
    DDRA = 0xFF;
    MotorsController::initialization();
    usart::initialization();

    RerunManager::initialization();
    RerunManager::setRerunManagerState(RerunManagerState::MEMORIZING);
    
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(70);
    MotorsController::setRightPercentage(70);
    _delay_ms(1000);
    MotorsController::setLeftPercentage(0);
    _delay_ms(500);
    MotorsController::setRightPercentage(0);
    
    // _delay_ms(5000);
    RerunManager::setRerunManagerState(RerunManagerState::RERUN);
    // Robot should rerun
    // _delay_ms(5000);

    while (true) {
    }
}