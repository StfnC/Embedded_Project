#define F_CPU 8000000L

#include "RerunManager.h"
#include <util/delay.h>

uint16_t RerunManager::address_ = 0;
Memoire24CXXX RerunManager::memory_ = Memoire24CXXX();
RerunManagerState RerunManager::state_ = RerunManagerState::INERT;

void RerunManager::manageRerun() {
    switch (state_) {
        case RerunManagerState::INERT:
            break;
        case RerunManagerState::MEMORIZING:
            writeMemory();
            break;
        case RerunManagerState::RERUN:
            readMemory();
            break;
    }
}


void RerunManager::setRerunManagerState(RerunManagerState state) {
    state_ = state;
}


void RerunManager::stopRegister(){
    stopRerunManagement();
    state_ = RerunManagerState::INERT;
    memory_.ecriture(address_++, 0xFF);
    memory_.ecriture(address_++, 0xFF);
}

void RerunManager::initializationRead() {
    initialization();
    address_ = 0;
    state_ = RerunManagerState::RERUN;
}

void RerunManager::initialization() {
    cli();

    TCNT2 = 0;
    TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A);

    OCR2A = TIMER_DURATION;

    sei();
}

void RerunManager::stopRerunManagement() {
    cli();

    TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1));
    OCR2A = 0x0000;
    TIMSK2 &= ~(_BV(OCIE2A));
    sei();
}

void RerunManager::stopRerun() {
    stopRerunManagement();
    state_ = RerunManagerState::INERT;
    MotorsController::setLeftPercentage(0);
    MotorsController::setRightPercentage(0);
}


void RerunManager::writeMemory() {
    uint8_t storingLeft = (MotorsController::getLeftDirection() << 7) | MotorsController::getLeftPercentage();
    memory_.ecriture(address_++, storingLeft);
    _delay_ms(1);
    uint8_t storingRight = (MotorsController::getRightDirection() << 7) | MotorsController::getRightPercentage();
    memory_.ecriture(address_++, storingRight);
}

void RerunManager::readMemory() {
    uint8_t lecture;
    memory_.lecture(address_++, &lecture);

    if (lecture == 0xFF) {
        stopRerun();
    }
    
    MotorsController::changeLeftDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setLeftPercentage(lecture & 0x7F);
    _delay_ms(1);
    memory_.lecture(address_++, &lecture);
    MotorsController::changeRightDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setRightPercentage(lecture & 0x7F);

}
