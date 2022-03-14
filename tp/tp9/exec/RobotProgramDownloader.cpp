#include "RobotProgramDownloader.h"

#include <memoire_24.h>
#include <usart.h>

RobotProgramDownloader::RobotProgramDownloader() : receivedData_(false), receptor_(), memory_(), totalBytes_(0xFFFF) {
}

void RobotProgramDownloader::acceptProgramData() {
    uint8_t firstBytesOfNumberOfBytes;

    while (totalBytes_ == 0xFFFF) {
        firstBytesOfNumberOfBytes = receptor_.receive();

        totalBytes_ = static_cast<uint16_t>(firstBytesOfNumberOfBytes) << 0x08;
        totalBytes_ += receptor_.receive();
    }

    memory_.ecriture(0x0000, static_cast<const uint8_t>(totalBytes_ >> 0x08));
    memory_.ecriture(0x0000 + sizeof(uint8_t), static_cast<const uint8_t>((totalBytes_ << 0x08) >> 0x08));
    
    receivedData_ = true;
}

bool RobotProgramDownloader::receivedData() {
    return receivedData_;
}