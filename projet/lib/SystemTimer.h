/**
 * Defintion of the RobotProgramDownloader class
 * 
 * \file SystemTimer.h
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 * 
 *  Output:
 * 
 */


#pragma once

#include <avr/io.h>

class SystemTimer {
    public:
        static void init();
        static void start();
        static void stop();
        static void incrementTimer();
        static inline uint32_t getTimer() {
            return timerCount_;
        }

    private:
        static const uint8_t ONE_MS_WITH_32_PRESCALER = 125;
        static uint32_t timerCount_;
};
