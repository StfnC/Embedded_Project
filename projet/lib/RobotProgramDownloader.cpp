/**
 * Implementation of the RobotProgramDownloader methods
 * 
 * \file RobotProgramDownloader.cpp
 * \author Stefan Cotargasanu
 * \date March 22 2022
 *  
 */

#define F_CPU 8000000

#include "RobotProgramDownloader.h"

#include "debug.h"
#include "memoire_24.h"
#include <util/delay.h>

RobotProgramDownloader::RobotProgramDownloader() : memory_(), totalBytes_(0x0000) {
}

void RobotProgramDownloader::acceptProgramData() {
    writeTotalBytes();
    writeProgramToMemory();
}

void RobotProgramDownloader::writeTotalBytes() {
    uint16_t firstByteOfNumberOfBytes = static_cast<uint16_t>(usart::receive());
    uint16_t secondByteOfNumberOfBytes = static_cast<uint16_t>(usart::receive());

    totalBytes_ |= firstByteOfNumberOfBytes << 0x08 | secondByteOfNumberOfBytes;

    memory_.ecriture(0x0000, static_cast<const uint8_t>(totalBytes_ >> 0x08));
    _delay_ms(5);
    memory_.ecriture(0x0000 + 1, static_cast<const uint8_t>(totalBytes_));
    _delay_ms(5);
}

void RobotProgramDownloader::writeProgramToMemory() {
    uint8_t dataBuffer;

    for (uint16_t i = 2; i < totalBytes_; i++) {
        dataBuffer = usart::receive();
        memory_.ecriture(0x0000 + i, dataBuffer);
        _delay_ms(5);
    }
}
