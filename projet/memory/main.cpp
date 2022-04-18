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
    RerunManager::writeMemory();
}

void wipeMemory() {
    Memoire24CXXX memory;

    for (uint16_t i = 0; i < UINT16_MAX; i++) {
        memory.ecriture(i, 0);
    }
}


int main() {
    DDRA |= 0x00;

    wipeMemory();

    usart::initialization();
    // usart::transmitTextMessage("CALIBRATION LUMIERE AMBIANTE\n");
    MotorsController::initialization();
    // LightController::initialization();
    // usart::transmitTextMessage("\nFIN CALIBRATION LUMIERE AMBIANTE\n");

    RerunManager::initialization();
    RerunManager::setIntervalle(255);
    
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(70);
    MotorsController::setRightPercentage(70);
    _delay_ms(1000);
    MotorsController::setLeftPercentage(0);
    _delay_ms(500);
    MotorsController::setRightPercentage(0);

}