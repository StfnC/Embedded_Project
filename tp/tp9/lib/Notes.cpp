#include "Notes.h"

Notes::Notes() : counter_() {
    
    counter_.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter_.setCompareMode(CompareMode::Toggle);
}

void Notes::playNote(uint8_t note) {
    cli();
    counter_.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter_.setCompareMode(CompareMode::Toggle);
    
    note = note - 45;
    uint16_t frequency = notes[note];
    uint16_t ocr = ( ( 8000000 / frequency ) - 2048 ) /  2048; 
    OCR1A = ocr;
    sei();
}

void Notes::stopNote() {
    counter_.setCompareMode(CompareMode::Off);
    OCR1A = 0;
}