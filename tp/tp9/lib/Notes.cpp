#include "Notes.h"
#include <math.h>
#define F_CPU 8000000 

Notes::Notes() : counter_(), transmitter_() {
    DDRD |= _BV(DDD5);
    counter_.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter_.setCompareMode(CompareMode::Off);
    OCR1A = 0;
}


void Notes::playNote(uint8_t note) {
    counter_.setCompareMode(CompareMode::Toggle);
    transmitter_.transmit(0xAA);
    uint16_t frequency = 440 * pow(2, (note - 69) / 12);
    uint16_t ocr = F_CPU / (2 * 1024 * frequency) - 1;
    
    transmitter_.transmit(0xBB);
    // END COPYRIGHT 
    cli();
    transmitter_.transmit(0xCC);
    OCR1A = ocr;
    TCNT1 = 0;
    sei();
    transmitter_.transmit(0xDD);
}

void Notes::stopNote() {
    counter_.setCompareMode(CompareMode::Off);
}

// Notes::Notes() {
//     TCNT1 = 0;
//     TCCR1A = _BV(COM2A0);
//     TCCR1B = _BV(WGM22) | _BV(CS12) | _BV(CS10);;
//     TCCR1C = 0;
//     TIMSK1 = _BV(OCIE1A);
// }

// void Notes::playNote(uint8_t note) {
//     float frequency = 440 * pow(2, (note - 69) / 12);
//     float duration = 1 / (2 * frequency);
//     float presqualer_value = F_CPU / 1024;
//     float ocr = duration * presqualer_value;
//     transmitter_.transmit(0xBB);
//     cli();
//     transmitter_.transmit(0xCC);
//     OCR1A = ocr;
//     sei();
// }