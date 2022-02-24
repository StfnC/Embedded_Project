/**
 * Problème 1 du TP4
 * Ce code implémente la machine à états du 2e problème du TP2 en utilisant les interruptions
 * La machine est implémentée en Moore et présente 3 états.
 * 
 * \file pb1.cpp
 * \author Stefan Cotargasanu et Justine Sauquet
 * \date 31 Janvier 2022
 * 
 * Broches:
 *  Input:
 *      -D2
 *      -D3
 *  Output:
 *      -A0
 *      -A1
 * 
 * Dans le tableau des états, on ne présente pas les possibilités que D2 et D3 soient à 1 en même temps,
 * car cela n'est pas possible sur SimulIDE
 * 
 * Tableau 1 : Tableau des états du problème 2
 * 
 * +--------------+----+----+--------------+-----------+-----------+
 * | État présent | D2 | D3 | État suivant | Sortie A1 | Sortie A0 |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_ROUGE | 0  | 0  | ALLUME_ROUGE | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_ROUGE | 0  | 1  | ALLUME_VERT  | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_ROUGE | 1  | 0  | ALLUME_VERT  | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_VERT  | 0  | 0  | ALLUME_VERT  | 0         | 1         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_VERT  | 0  | 1  | ETEINT       | 0         | 1         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME_VERT  | 1  | 0  | ALLUME_ROUGE | 0         | 1         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ETEINT       | 0  | 0  | ETEINT       | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ETEINT       | 0  | 1  | ALLUME_ROUGE | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ETEINT       | 1  | 0  | ALLUME_VERT  | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * 
*/

#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Etat.hpp"

const double TEMPS_DEBOUNCE = 10;

// FIXME:  ??? Variable globale ???
volatile Etat etatMachine = Etat::ALLUME_ROUGE;

// placer le bon type de signal d'interruption

void gererAppuiD2() {
    switch (etatMachine) {
        case Etat::ALLUME_ROUGE:
            etatMachine = Etat::ALLUME_VERT;
            break;
        case Etat::ALLUME_VERT:
            etatMachine = Etat::ALLUME_ROUGE;
            break;
        case Etat::ETEINT:
            etatMachine = Etat::ALLUME_VERT;
            break;
    }
}

void gererAppuiD3() {
    switch (etatMachine) {
        case Etat::ALLUME_ROUGE:
            etatMachine = Etat::ALLUME_VERT;
            break;
        case Etat::ALLUME_VERT:
            etatMachine = Etat::ETEINT;
            break;
        case Etat::ETEINT:
            etatMachine = Etat::ALLUME_ROUGE;
            break;
    }
}

// à prendre en charge en argument
ISR(INT0_vect) {
    // laisser un délai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

    _delay_ms(TEMPS_DEBOUNCE);

    // se souvenir ici si le bouton est pressé ou relâché

    // 'modifier ici'

    // changements d'état tels que ceux de la

    // semaine précédente

    gererAppuiD2();

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0);
}

ISR(INT1_vect) {
    // laisser un délai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

    _delay_ms(TEMPS_DEBOUNCE);

    // se souvenir ici si le bouton est pressé ou relâché

    // 'modifier ici'

    // changements d'état tels que ceux de la

    // semaine précédente

    gererAppuiD3();

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF1);
}

void initialisation() {
    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontrôleur n'est pas prêt...

    cli();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) | (1 << INT1);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC01) | (1 << ISC00);
    EICRA |= (1 << ISC11) | (1 << ISC10);

    // sei permet de recevoir à nouveau des interruptions.

    sei();
}

void allumerDelRouge() {
    PORTA &= ~(1 << DDA0);
    PORTA |= 1 << DDA1;
}

void allumerDelVerte() {
    PORTA |= 1 << DDA0;
    PORTA &= ~(1 << DDA1);
}

void eteindreDel() {
    PORTA &= ~(1 << DDA0) & ~(1 << DDA1);
}

void gererMachineAEtats() {
    switch (etatMachine) {
        case Etat::ALLUME_ROUGE:
            allumerDelRouge();
            break;
        case Etat::ALLUME_VERT:
            allumerDelVerte();
            break;
        case Etat::ETEINT:
            eteindreDel();
            break;
    }
}

int main() {
    // Inspiré par le code d'un des chargés sur le TP1 (pour set les modes des pins et pour lire les pins)

    initialisation();

    while (true) {
        gererMachineAEtats();
    }

    return 0;
}