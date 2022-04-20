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
        RobotProgramDownloader(uint16_t startingAddress);

        void acceptProgramData();
    private:
        Memoire24CXXX memory_;
        uint16_t totalBytes_;
        uint16_t startingAddress_;

        void writeTotalBytes();
        void writeProgramToMemory();
};