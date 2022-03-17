#define F_CPU 8000000

#include "RobotProgramDownloader.h"

#include <debug.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>

RobotProgramDownloader::RobotProgramDownloader() : receivedData_(false), receptor_(), memory_(), totalBytes_(0xFFFF) {
}

void RobotProgramDownloader::acceptProgramData() {
    uint8_t firstByteOfNumberOfBytes;
    uint8_t secondByteOfNumberOfBytes;

    firstByteOfNumberOfBytes = receptor_.receive();

    totalBytes_ = static_cast<uint16_t>(firstByteOfNumberOfBytes) << 0x08;

    secondByteOfNumberOfBytes = receptor_.receive();

    totalBytes_ += secondByteOfNumberOfBytes;

    memory_.ecriture(0x0000, static_cast<const uint8_t>(totalBytes_ >> 0x08));
    _delay_ms(5);
    memory_.ecriture(0x0000 + sizeof(uint8_t), static_cast<const uint8_t>((totalBytes_ << 0x08) >> 0x08));

    receivedData_ = true;
}

bool RobotProgramDownloader::receivedData() {
    return receivedData_;
}