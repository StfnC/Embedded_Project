/**
 * Definition of the RobotProgramDownloader class
 * 
 * \file RobotProgramDownloader.h
 * \author Stefan Cotargasanu
 * \date March 22 2022
 *  
 */

#include "memoire_24.h"
#include "usart.h"

class RobotProgramDownloader {
    public:
        RobotProgramDownloader();

        void acceptProgramData();
    private:
        static constexpr uint8_t VALUE_TO_SHIFT_EIGHT_FIRST_BITS = 8;
        static constexpr uint8_t FIVE_MS_DELAY = 5;
        static constexpr uint8_t START_OF_INSTRUCTIONS = 2;
        Memoire24CXXX memory_;
        uint16_t totalBytes_;
        
        void writeTotalBytes();
        void writeProgramToMemory();
};