/**
Program implementing the color of a led from an input of the ADC.
 \file   pb1.cpp
 \author Rakotoarivony Faneva #2131367 and Lina Belloui #...
 \date   february 14 2022
Created february 21 2022

PIN A A (0 : ADC)
PIN B OUT  (D0 D1 : DEL)
**/


#include <avr/eeprom.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"

const uint8_t RED = _BV(1);
const uint8_t GREEN = _BV(0);
const uint8_t OFF = 0x00;
const uint8_t PRECISION = 2;

const uint8_t LOW_LIGHT = 170;
const uint8_t HIGH_LIGHT = 220;


void setColor(uint8_t color)
{
    PORTB = color;
}

int main()
{
    DDRA = 0x00;
    DDRB = _BV(PORTB0) | _BV(PORTB1);
    can converter = can();
    uint16_t value;
    while (true)
    {


        value = converter.lecture(PORTA0);

    
        uint8_t significantValue = (value >> PRECISION); 
        
        if (significantValue < LOW_LIGHT)
        {
            setColor(GREEN);
        }
        else if (significantValue > HIGH_LIGHT)
        {
            setColor(RED);
        }
        else 
        {
            setColor(GREEN);
            _delay_ms(1);
            setColor(RED);
            _delay_ms(1);
        }
        
    }
}