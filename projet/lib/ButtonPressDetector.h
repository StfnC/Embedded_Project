/**
 * Implements methods of ButtonPressDetector Class
 * 
 * \file ButtonPressDetector.h
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 *      Motherboard Button:
 *          -D2
 *      Breadboard Button:
 *          -D3
 *  Output:
 * 
 */

#pragma once

#include <avr/io.h>

class ButtonPressDetector {
    public:
        static void init();

        static bool isBreadButtonPressed();
        static bool isSmallButtonPressed();

    private:
        static const uint8_t DEBOUNCE_TIME = 10;
};
