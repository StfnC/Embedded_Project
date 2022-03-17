#define F_CPU 8000000

#include "RobotProgramDownloader.h"

#include <debug.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>

RobotProgramDownloader::RobotProgramDownloader() : receptor_(), memory_(), totalBytes_(0x0000) {
}

void RobotProgramDownloader::acceptProgramData() {
    writeTotalBytes();

    uint8_t dataBuffer;

    for (uint16_t i = 2; i < totalBytes_; i++) {
        dataBuffer = receptor_.receive();
        memory_.ecriture(0x0000 + i * sizeof(uint8_t), dataBuffer);
        _delay_ms(5);
    }
}

void RobotProgramDownloader::writeTotalBytes() {
    uint16_t firstByteOfNumberOfBytes = static_cast<uint16_t>(receptor_.receive());
    uint16_t secondByteOfNumberOfBytes = static_cast<uint16_t>(receptor_.receive());

    totalBytes_ |= firstByteOfNumberOfBytes << 0x08 | secondByteOfNumberOfBytes;

    memory_.ecriture(0x0000, static_cast<const uint8_t>(totalBytes_ >> 0x08));
    _delay_ms(5);
    memory_.ecriture(0x0000 + sizeof(uint8_t), static_cast<const uint8_t>(totalBytes_));
    _delay_ms(5);
}
