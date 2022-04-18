#define F_CPU 8000000
#include <LightController.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <counter.h>
#include <usart.h>
#include <MemoryManager.h>
#include <MotorsController.h>
volatile bool gMinuterieExpiree = true;
volatile int valeurAvantInterruption;
volatile int valeurApresInterruption;
volatile int counter = 0;

volatile bool rerun = true;

ISR(TIMER2_COMPA_vect)
{
    if (MemoryManager::state_ == State::MEMORIZING)
    {
        MemoryManager::writeMemory();
    }
    else if (MemoryManager::state_ == State::RERUN)
    {
        MemoryManager::readMemory();
    }
    else {}
}

int main()
{
    DDRA |= 0x00;

    usart::initialization();
    // usart::transmitTextMessage("CALIBRATION LUMIERE AMBIANTE\n");
    MotorsController::initialization();
    // LightController::initialization();
    // usart::transmitTextMessage("\nFIN CALIBRATION LUMIERE AMBIANTE\n");
    MemoryManager::state_ = State::RERUN;
    MemoryManager::initialization();
    MemoryManager::setIntervalle(255);

    // MotorsController::changeLeftDirection(Direction::Forward);
    // MotorsController::changeRightDirection(Direction::Forward);
    // MotorsController::setLeftPercentage(70);
    // MotorsController::setRightPercentage(70);
    // _delay_ms(1000);
    // MotorsController::setLeftPercentage(0);
    // _delay_ms(500);
    // MotorsController::setRightPercentage(0);

    while (true)
        ;
}