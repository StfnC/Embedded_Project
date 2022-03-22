
#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <counter.h>

#include "Notes.h"
#include "Notes.cpp"


// au clare de la lune
class Partition {

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
};

// He's a pirate

class Partition {

    void Partition() {

        Notes note = Notes();

        _delay_ms(166);
        note.playNote(55); // sol croche

        _delay_ms(166);
        note.playNote(60); // do croche 

        _delay_ms(331);
        note.playNote(62); // ré noir

       _delay_ms(331);
        note.playNote(62);

       _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(64); // mi croche  

        _delay_ms(331);
        note.playNote(65); // fa noir

        _delay_ms(331);
        note.playNote(65);

        _delay_ms(166);
        note.playNote(65); // fa croche 

        _delay_ms(166);
        note.playNote(67); // sol 3

        _delay_ms(331);
        note.playNote(64);
        
        _delay_ms(331);
        note.playNote(64);

        _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(60);

        _delay_ms(166);
        note.playNote(60);

        _delay_ms(331);
        note.playNote(62);

        _delay_ms(166);
        // demi soupir

        _delay_ms(166);
        note.playNote(55); // sol croche

        _delay_ms(166);
        note.playNote(60); // do croche 

        _delay_ms(331);
        note.playNote(62); // ré noir

       _delay_ms(331);
        note.playNote(62);

       _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(64); // mi croche  

        _delay_ms(331);
        note.playNote(65); // fa noir

        _delay_ms(331);
        note.playNote(65);

        _delay_ms(166);
        note.playNote(65); // fa croche 

        _delay_ms(166);
        note.playNote(67); // sol 3

        _delay_ms(331);
        note.playNote(64);
        
        _delay_ms(331);
        note.playNote(64);

        _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(60);

        _delay_ms(497);
        note.playNote(62);

        _delay_ms(166);
        

        _delay_ms(166);
        note.playNote(55); // sol croche

        _delay_ms(166);
        note.playNote(60); // do croche 

        _delay_ms(331);
        note.playNote(62); // ré noir

       _delay_ms(331);
        note.playNote(62);

       _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(65); // fa croche 

        _delay_ms(331);
        note.playNote(67);

        _delay_ms(331);
        note.playNote(67);

        _delay_ms(166));
        note.playNote(67);

        _delay_ms(166));
        note.playNote(69); // la croche

        _delay_ms(331);
        note.playNote(71);

        _delay_ms(331);
        note.playNote(71); // si noir

        _delay_ms(166));
        note.playNote(69);

        _delay_ms(166);
        note.playNote(67); // sol3 croche

        _delay_ms(166));
        note.playNote(69);

        _delay_ms(331);
        note.playNote(62);

        _delay_ms(166);
        note.playNote();

        _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(64);

        _delay_ms(331);
        note.playNote(65);

        _delay_ms(331);
        note.playNote(65);

        _delay_ms(331);
        note.playNote(67);

        _delay_ms(166);
        note.playNote(69);

        _delay_ms(331);
        note.playNote(62);

        _delay_ms(166);
        note.playNote();

        _delay_ms(166);
        note.playNote(62);
    
        _delay_ms(166);
        note.playNote(65);

        _delay_ms(331);
        note.playNote(64);

        _delay_ms(331);
        note.playNote(64);

        _delay_ms(166);
        note.playNote(65);

        _delay_ms(166);
        note.playNote(62);

        _delay_ms(497);
        note.playNote(62);

        _delay_ms(166);




        
        _delay_ms(166);
        note.playNote(69); // la croche

        _delay_ms(166);
        note.playNote(72); // do croche 

        _delay_ms(331);
        note.playNote(74); // ré noir

       _delay_ms(331);
        note.playNote(74);

       _delay_ms(166);
        note.playNote(74);

        _delay_ms(166);
        note.playNote(77); // fa croche  

        _delay_ms(331);
        note.playNote(79); // sol noir

        _delay_ms(331);
        note.playNote(79);

        _delay_ms(166);
        note.playNote(79); // sol croche 

        _delay_ms(166);
        note.playNote(67); // sol 3 ///

        _delay_ms(331);
        note.playNote(64);
        
        _delay_ms(331);
        note.playNote(64);

        _delay_ms(166);
        note.playNote(62);

        _delay_ms(166);
        note.playNote(60);

        _delay_ms(166);
        note.playNote(60);

        _delay_ms(331);
        note.playNote(62);

        _delay_ms(166);

    };
};
