#define F_CPU 8000000L

#include "RerunManager.h"

#include <util/delay.h>

uint16_t RerunManager::address_ = 0;
Memoire24CXXX RerunManager::memory_ = Memoire24CXXX();
RerunManagerState RerunManager::state_ = RerunManagerState::INERT;
uint32_t RerunManager::lastMemoryAccess_ = 0;

void RerunManager::manageRerun() {
    if (SystemTimer::getTimer() >= lastMemoryAccess_ + MEMORY_ACCESS_INTERVAL) {
        lastMemoryAccess_ = SystemTimer::getTimer();

        switch (state_) {
            case RerunManagerState::INERT:
            case RerunManagerState::END_MEMORY:
                break;
            case RerunManagerState::MEMORIZING:
                writeMemory();
                break;
            case RerunManagerState::RERUN:
                readMemory();
                break;
        }
    }
}

void RerunManager::setRerunManagerState(RerunManagerState state) {
    state_ = state;
}

void RerunManager::stopRegister() {
    state_ = RerunManagerState::END_MEMORY;

    memory_.ecriture(address_++, END_OF_RERUN_MARKER);
    memory_.ecriture(address_++, END_OF_RERUN_MARKER);
}

void RerunManager::initializationRead() {
    address_ = 0;
    state_ = RerunManagerState::RERUN;
}

void RerunManager::stopRerun() {
    state_ = RerunManagerState::END_MEMORY;

    MotorsController::setLeftPercentage(0);
    MotorsController::setRightPercentage(0);
}

void RerunManager::writeMemory() {
    uint8_t storingLeft = (MotorsController::getLeftDirection() << VALUE_FOR_SHIFT_EIGHTH_BIT) | MotorsController::getLeftPercentage();
    memory_.ecriture(address_++, storingLeft);
    _delay_ms(1);
    uint8_t storingRight = (MotorsController::getRightDirection() << VALUE_FOR_SHIFT_EIGHTH_BIT) | MotorsController::getRightPercentage();
    memory_.ecriture(address_++, storingRight);
}

void RerunManager::readMemory() {
    uint8_t lecture;
    memory_.lecture(address_++, &lecture);

    if (lecture == END_OF_RERUN_MARKER) {
        stopRerun();
    }

    MotorsController::changeLeftDirection(static_cast<Direction>(lecture >> VALUE_FOR_SHIFT_EIGHTH_BIT));
    MotorsController::setLeftPercentage(lecture & SEVEN_FIRST_BITS_MASK);
    _delay_ms(1);
    memory_.lecture(address_++, &lecture);
    MotorsController::changeRightDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setRightPercentage(lecture & SEVEN_FIRST_BITS_MASK);
    
    if (lecture == END_OF_RERUN_MARKER) {
        stopRerun();
    }
}