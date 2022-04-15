#include "MemoryManager.h"

uint16_t MemoryManager::address_ = 0;
Memoire24CXXX MemoryManager::memory = Memoire24CXXX();


void MemoryManager::initializationRead() {
    MemoryManager::initialization();
    address_ = 0;
}

void MemoryManager::initialization() {
    cli();
    TCNT0 = 0;
    TCCR0A = _BV(COM0A1) | _BV(COM0A0) | _BV(COM0B1) | _BV(COM0B0);
    TCCR0B |= (1 << CS12) | (1 << CS10);
    TIMSK0 |= (1 << OCIE0A); // | (1<<OCIE0B);
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
