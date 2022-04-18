#include "MemoryManager.h"

uint16_t MemoryManager::address_ = 0;
Memoire24CXXX MemoryManager::memory = Memoire24CXXX();
State MemoryManager::state_ = State::INERT;

void MemoryManager::initializationRead() {
    MemoryManager::initialization();
    address_ = 0;
}

void MemoryManager::manageRun() {
    switch (state_)
    {
    case State::INERT:
        break;
    case State::MEMORIZING:
        writeMemory();
        break;
    case State::RERUN:
        readMemory();
        break;
    }
}

void MemoryManager::initialization() {
    usart::initialization();
    cli();
    TCNT2 = 0;
    TCCR2A = _BV(COM2A1) | _BV(COM2A0) | _BV(3);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    TIMSK2 |= (1 << OCIE2A);
    sei();
}

void MemoryManager::setIntervalle(uint16_t duration) {
    OCR2A = duration;
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
    // usart::transmitTextMessage("\tAddr : %d", address_ >> 8);
    // usart::transmitTextMessage("%d", static_cast<uint8_t>(address_));
    // usart::transmitTextMessage(" Value : %d", lecture);

    memory.lecture(address_++, &lecture);
    MotorsController::changeRightDirection(static_cast<Direction>(lecture >> 7));
    MotorsController::setRightPercentage(lecture & 0x7F);
    // usart::transmitTextMessage("\tAddr : %d", address_ >> 8);
    // usart::transmitTextMessage("%d", static_cast<uint8_t>(address_));
    // usart::transmitTextMessage(" Value : %d \n", lecture);

}
