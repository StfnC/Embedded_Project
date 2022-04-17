/**
 * Definition of the lightController class
 *
 * \file lightController.h
 * \author Rakotoarivony Faneva
 * \date April 6 2022
 */

#pragma once
#include <avr/io.h>
#include <stdlib.h>
#include "can.h"
#include <MotorsController.h>
#include <debug.h>
#include <usart.h>
#include <led.h>

class LightController {
    public:
        static void initialization();
        static void followLight();
        static void averageLightCalculation();

    private:
        static void frontLight();
        static void middleLight();
        static void noLightLeft();
        static void noLightRight();
        static uint8_t readValue(uint8_t port);
        
        static const uint8_t OCR_PRECISION = 5;
        static const uint8_t DEFAULT_SPEED = 50;
        static const uint8_t PRECISION_CAN = 2;
        static const uint8_t MIDDLE_VALUE = 128;
        static uint8_t leftValue_;
        static uint8_t rightValue_;
        static uint8_t ocrLeft_;
        static uint8_t ocrRight_;
        static uint8_t highestAmbientValue_;
        static uint8_t middleValue_;
        static can converter_;
        static MotorsController motors_;
};