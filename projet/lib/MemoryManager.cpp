#include "MemoryManager.h"

uint16_t MemoryManager::address_ = 0;
Memoire24CXXX MemoryManager::memory = Memoire24CXXX();


void MemoryManager::initializationRead() {
    MemoryManager::initialization();
    address_ = 0;
}

void MemoryManager::initialization() {
    usart::initialization();
    cli();
    TCNT1 = 0;
    TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0);
    TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A); // | (1<<OCIE0B);
    sei();
}

void MemoryManager::setIntervalle(uint16_t duration) {
    OCR1A = duration;
}

void MemoryManager::writeMemory() {
    uint8_t storingLeft = (MotorsController::getLeftDirection() << 7) | MotorsController::getLeftPercentage();
    memory.ecriture(address_++, storingLeft);
    // usart::transmitTextMessage("Addr : %d", address_);
    // usart::transmitTextMessage("\tValue : %d", storingLeft);
    uint8_t storingRight = (MotorsController::getRightDirection() << 7) | MotorsController::getRightPercentage();
    memory.ecriture(address_++, storingRight);
    // usart::transmitTextMessage("\tAddr : %d", address_);
    // usart::transmitTextMessage("\tValue : %d\n", storingRight);
}

void MemoryManager::readMemory() {
    uint8_t lecture;
    memory.lecture(address_++, &lecture);
    MotorsController::changeLeftDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setLeftPercentage(lecture & 0x7F);
    // usart::transmitTextMessage("Addr : %d", address_);
    // usart::transmitTextMessage(" Value : %d", lecture);

    memory.lecture(address_++, &lecture);
    MotorsController::changeRightDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setRightPercentage(lecture & 0x7F);
    // usart::transmitTextMessage("\tAddr : %d", address_);
    // usart::transmitTextMessage(" Value : %d \n", lecture);

}
