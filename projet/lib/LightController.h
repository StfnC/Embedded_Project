/**
 * Definition of the lightController class
 *
 * \file lightController.h
 * \author Rakotoarivony Faneva
 * \date April 6 2022
 */

#pragma once
#include <avr/io.h>
#include "can.h"
#include <MotorsController.h>
#include <debug.h>
#include <usart.h>


class LightController {
    public:
        static void initialization();
        static void followLight();
        static void averageLightCalculation();

    private:
        static void frontLight();
        static void middleLight();
        static void farLeftLight();
        static void farRightLight();
        static uint8_t readValue(uint8_t port);
        static const uint8_t HIGH_VALUE_LIGHT = 20;
        static const uint8_t MIDDLE_VALUE = 128;
        static uint8_t leftValue_;
        static uint8_t rightValue_;
        static uint16_t average_;
        static uint8_t middleValue_;
        static can converter_;
        static MotorsController motors_;
};