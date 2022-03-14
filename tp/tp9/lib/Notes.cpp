#include "Notes.h"

void Notes::notePWM(int note)
{
    acitf
}
void Notes::playNote(int note, double temps)
{
    acitf
}

void Notes::offNote()
{
    TCNT0 = 0;
    OCR0A = 0;  
    TCCR0A = 0;
    TCCR0B = 0;
}
