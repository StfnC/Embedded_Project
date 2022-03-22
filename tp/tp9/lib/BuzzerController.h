/**
 * Definition of the BuzzerController class
 * 
 * \file MotorsController.h
 * \author Stefan Cotargasanu
 * \date March 13 2022
 * * Pins:
 *  Input:
 *      -
 *
 *  Output:
 *      -D4
 *      -D5
 *  
 */

#pragma once
#include <avr/io.h>

class BuzzerController {
    public:
        static void initBuzzer();
        static void playNote(uint8_t note);
        static void stopNote();

        static const uint16_t OCR_VALUES[37];
};