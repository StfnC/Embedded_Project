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
        Memoire24CXXX memory_;
        uint16_t totalBytes_;

        void writeTotalBytes();
        void writeProgramToMemory();
};