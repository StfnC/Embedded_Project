#define F_CPU 8000000
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
    RerunManager::readMemory();
    // gMinuterieExpiree = true;
}




int main() {
    DDRA |= 0x00;


    usart::initialization();
    usart::transmitTextMessage("CALIBRATION LUMIERE AMBIANTE\n");
    MotorsController::initialization();
    usart::transmitTextMessage("\nFIN CALIBRATION LUMIERE AMBIANTE\n");

    RerunManager::initialization();
    
    while (counter < INT8_MAX);
    {   
        if (gMinuterieExpiree) {
            RerunManager::readMemory();
            gMinuterieExpiree = false;
        }
    }
}