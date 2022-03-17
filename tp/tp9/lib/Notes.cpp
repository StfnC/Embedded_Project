#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <conter.h>
#include "Notes.h"

//void Notes::notePWM(int note)
//{
//    acitf
//}
//void Notes::playNote(int note, double temps)
//{
//    acitf
//}


const uint8_t partition[] =
{
    Do3, Re3, Mi3, Fa3, Sol3, La3, Si3, Do4
}

// formule (1+x) = 8000 * note / 2*1024

{
    CounterInterrupt conter = CounterInterrupt();
    conter.setGenerationMode(GenerationMode::ClearTimerCompare);
    conter.setCompareMode(CompareMode::LowLevel);

   // activer compteur .set (CTC) duration a valur obtenur <=> la 
    
    for (int i=0, i< sizeof.partition, i++) {
        uint16_t x = ((8000 * partition[i]) / (2 * 1024));
        conter.setDuration(x); 
    }
    
}

void Notes::offNote()
{
    TCNT0 = 0;
    OCR0A = 0;  
    TCCR0A = 0;
    TCCR0B = 0;
}
