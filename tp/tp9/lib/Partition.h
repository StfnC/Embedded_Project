
#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <counter.h>

#include "Notes.h"
#include "Notes.cpp"


// au clare de la lune

void Partition() {

    Notes note = Notes();

    _delay_ms(600);
    note.playNote(60); 

    _delay(600);
    note.playNote(60); 

    _delay(600);
    note.playNote(60); 

    _delay(600);
    note.playNote(62);

    _delay(1200);
    note.playNote(64);

    _delay(1200);
    note.playNote(62);

    _delay(600);
    note.playNote(60);

    _delay(600);
    note.playNote(64);

    _delay(600);
    note.playNote(62);

    _delay(600);
    note.playNote(62);

    _delay(2400);
    note.playNote(60);

};
