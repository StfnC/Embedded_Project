/**
 * Definition of the usart class
 * 
 * \file usart.h
 * \author Stefan Cotargasanu
 * \date March 13 2022
  * Pins:
 *  Input:
 *      -D0
 * 
 *  Output:
 *      -D1
 * 
 */
#pragma once
#include <avr/io.h>

class usart {
    public:
        static void initialization(void);
        
        static void transmit(uint8_t data);
        static uint8_t receive(void);

        static void transmitTextMessage(const char message[]);
        static void transmitTextMessage(const char message[], uint8_t value);
        
    private:
        static constexpr uint8_t DEFAULT_MESSAGE_BUFFER_SIZE = 50;
};
