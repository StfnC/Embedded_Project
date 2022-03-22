/**
 * Definition of the Partition class
 * 
 * \file Partition.h
 * \author Justine Sauquet
 * \date March 22 2022
 *  
 */

#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include <BuzzerController.h>

class Partition {
public:
    void partitionPirates() {
        _delay_ms(166);
        BuzzerController::playNote(55); // sol croche

        _delay_ms(166);
        BuzzerController::playNote(60); // do croche 

        _delay_ms(331);
        BuzzerController::playNote(62); // ré noir

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(64); // mi croche  

        _delay_ms(331);
        BuzzerController::playNote(65); // fa noir

        _delay_ms(331);
        BuzzerController::playNote(65);

        _delay_ms(166);
        BuzzerController::playNote(65); // fa croche 

        _delay_ms(166);
        BuzzerController::playNote(67); // sol 3

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(60);

        _delay_ms(166);
        BuzzerController::playNote(60);

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);
        // demi soupir

        _delay_ms(166);
        BuzzerController::playNote(55); // sol croche

        _delay_ms(166);
        BuzzerController::playNote(60); // do croche 

        _delay_ms(331);
        BuzzerController::playNote(62); // ré noir

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(64); // mi croche  

        _delay_ms(331);
        BuzzerController::playNote(65); // fa noir

        _delay_ms(331);
        BuzzerController::playNote(65);

        _delay_ms(166);
        BuzzerController::playNote(65); // fa croche 

        _delay_ms(166);
        BuzzerController::playNote(67); // sol 3

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(60);

        _delay_ms(497);
        BuzzerController::playNote(62);

        _delay_ms(166);


        _delay_ms(166);
        BuzzerController::playNote(55); // sol croche

        _delay_ms(166);
        BuzzerController::playNote(60); // do croche 

        _delay_ms(331);
        BuzzerController::playNote(62); // ré noir

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(65); // fa croche 

        _delay_ms(331);
        BuzzerController::playNote(67);

        _delay_ms(331);
        BuzzerController::playNote(67);

        _delay_ms(166);
        BuzzerController::playNote(67);

        _delay_ms(166);
        BuzzerController::playNote(69); // la croche

        _delay_ms(331);
        BuzzerController::playNote(71);

        _delay_ms(331);
        BuzzerController::playNote(71); // si noir

        _delay_ms(166);
        BuzzerController::playNote(69);

        _delay_ms(166);
        BuzzerController::playNote(67); // sol3 croche

        _delay_ms(166);
        BuzzerController::playNote(69);

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(64);

        _delay_ms(331);
        BuzzerController::playNote(65);

        _delay_ms(331);
        BuzzerController::playNote(65);

        _delay_ms(331);
        BuzzerController::playNote(67);

        _delay_ms(166);
        BuzzerController::playNote(69);

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(65);

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(166);
        BuzzerController::playNote(65);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(497);
        BuzzerController::playNote(62);

        _delay_ms(166);

        _delay_ms(166);
        BuzzerController::playNote(69); // la croche

        _delay_ms(166);
        BuzzerController::playNote(72); // do croche 

        _delay_ms(331);
        BuzzerController::playNote(74); // ré noir

        _delay_ms(331);
        BuzzerController::playNote(74);

        _delay_ms(166);
        BuzzerController::playNote(74);

        _delay_ms(166);
        BuzzerController::playNote(77); // fa croche  

        _delay_ms(331);
        BuzzerController::playNote(79); // sol noir

        _delay_ms(331);
        BuzzerController::playNote(79);

        _delay_ms(166);
        BuzzerController::playNote(79); // sol croche 

        _delay_ms(166);
        BuzzerController::playNote(67); // sol 3 ///

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(331);
        BuzzerController::playNote(64);

        _delay_ms(166);
        BuzzerController::playNote(62);

        _delay_ms(166);
        BuzzerController::playNote(60);

        _delay_ms(166);
        BuzzerController::playNote(60);

        _delay_ms(331);
        BuzzerController::playNote(62);

        _delay_ms(166);
    };

    void partitionAuClair() {
        _delay_ms(600);
        BuzzerController::playNote(60);

        _delay_ms(600);
        BuzzerController::playNote(60);

        _delay_ms(600);
        BuzzerController::playNote(60);

        _delay_ms(600);
        BuzzerController::playNote(62);

        _delay_ms(1200);
        BuzzerController::playNote(64);

        _delay_ms(1200);
        BuzzerController::playNote(62);

        _delay_ms(600);
        BuzzerController::playNote(60);

        _delay_ms(600);
        BuzzerController::playNote(64);

        _delay_ms(600);
        BuzzerController::playNote(62);

        _delay_ms(600);
        BuzzerController::playNote(62);

        _delay_ms(2400);
        BuzzerController::playNote(60);
    };
};
