#include "MemoryManager.h"

uint16_t MemoryManager::address_ = 0;
Memoire24CXXX MemoryManager::memory = Memoire24CXXX();


void MemoryManager::initializationRead() {
    MemoryManager::initialization();
    address_ = 0;
}

void MemoryManager::initialization() {
    cli();
    TCNT2 = 0;
    TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(COM2B1) | _BV(COM2B0);
    TCCR2B |= (1 << CS22) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A); // | (1<<OCIE0B);
    sei();
}

void MemoryManager::setIntervalle(uint8_t duration) {
    OCR0A = duration;
}

void MemoryManager::writeMemory() {
    uint8_t storingLeft = (MotorsController::getLeftDirection() << 7) | MotorsController::getLeftPercentage();
    memory.ecriture(address_++, storingLeft);
    uint8_t storingRight = (MotorsController::getRightDirection() << 7) | MotorsController::getRightPercentage();
    memory.ecriture(address_++, storingRight);
}

void MemoryManager::readMemory() {
    uint8_t lecture;
    memory.lecture(address_++, &lecture);
    MotorsController::changeLeftDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setLeftPercentage(lecture & 0x7F);

    memory.lecture(address_++, &lecture);
    MotorsController::changeRightDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setRightPercentage(lecture & 0x7F);
}
