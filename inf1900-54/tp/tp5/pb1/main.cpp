#include <avr/eeprom.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "memoire_24.h"

uint8_t string[5] = "aaaa";
uint8_t longueur = 4;

bool validation(uint8_t* read,const uint8_t* given)
{
    bool valid = true;
    for (size_t i = 0; i < longueur; i++)
    {
        if (read[i] != given[i])
        {
            valid = false;
        } 
    }
    
    return valid;
}

int main()
{
    DDRA = 0xff;
    
    uint16_t startAdress = 0x0000;

    Memoire24CXXX memory = Memoire24CXXX();
    memory.ecriture(startAdress, &string[0], sizeof(uint8_t)*longueur);
    _delay_ms(100);
    
    uint8_t* memoryRead;
    memory.lecture(startAdress, memoryRead, longueur);

    if (validation(memoryRead, string))
    {
        PORTA = 0x01;
    }
    else
    {
        PORTA = 0x02;
    }
}