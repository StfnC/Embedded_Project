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
        usart();
        ~usart() = default;

        void transmit(uint8_t data);

        uint8_t receive(void);

        void transmitTextMessage(const char message[]);
        void transmitTextMessage(const char message[], uint8_t value);
        
    private:
        static const uint8_t DEFAULT_MESSAGE_BUFFER_SIZE = 50;
        void initialization(void);
        
};
