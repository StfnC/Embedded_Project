#include "Notes.h"
#include <math.h>

Notes::Notes() : counter_() {
    
    counter_.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter_.setCompareMode(CompareMode::Off);
    OCR1A = 0;
}

void Notes::playNote(uint8_t note) {
    counter_.setGenerationMode(GenerationMode::ClearTimerCompare);
    counter_.setCompareMode(CompareMode::Toggle);
    
    uint16_t frequency = 440 * pow(2, (note - 69) / 12);
    uint16_t ocr = 8000000 / (2 * 1024 * frequency) - 1;
    OCR1A = ocr;
}

void Notes::stopNote() {
    counter_.setCompareMode(CompareMode::Off);
}