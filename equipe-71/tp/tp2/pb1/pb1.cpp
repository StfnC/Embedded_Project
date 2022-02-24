/**
 * Problème 1 du TP2
 * Ce code permet d'allumer une DEL en rouge après 3 appuis d'un bouton.
 * Un second bouton permet de réinitialiser le nombre d'appuis.
 * Ce comportement est accompli en implémentant une machine de Mealy avec quatre états.
 * 
 * \file pb1.cpp
 * \author Stefan Cotargasanu et Justine Sauquet
 * \date 30 Janvier 2022
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
 * Tableau 1 : Tableau des états du problème 1
 * 
 * +--------------+----+----+--------------+-----------+-----------+
 * | État présent | D2 | D3 | État suivant | Sortie A1 | Sortie A0 |
 * +--------------+----+----+--------------+-----------+-----------+
 * | INIT         | 0  | 0  | INIT         | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | INIT         | 0  | 1  | INIT         | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | INIT         | 1  | 0  | APPUI_1      | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_1      | 0  | 0  | APPUI_1      | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_1      | 0  | 1  | INIT         | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_1      | 1  | 0  | APPUI_2      | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_2      | 0  | 0  | APPUI_2      | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_2      | 0  | 1  | INIT         | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | APPUI_2      | 1  | 0  | ALLUME       | 0         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME       | 0  | 0  | ALLUME       | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME       | 0  | 1  | INIT         | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * | ALLUME       | 1  | 0  | INIT         | 1         | 0         |
 * +--------------+----+----+--------------+-----------+-----------+
 * 
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#include "Etat.hpp"

const double TEMPS_APPUI_BOUTON = 10;

void bloquerBoutons() {
    while ((PIND & (1 << PIND2)) || (PIND & (1 << PIND3))) {
    }
}

bool verifierAppuiBouton(uint8_t port, uint8_t pin) {
    bool appuye = port & (1 << pin);
    if (appuye) {
        _delay_ms(TEMPS_APPUI_BOUTON);
        bloquerBoutons();
        return (port & (1 << pin));
    }
    return false;
}

void gererEtatInit(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::APPUI_1;
    }
    PORTA &= ~(1 << DDA0) & ~(1 << DDA1);
}

void gererEtatAppui1(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::APPUI_2;
    }
    PORTA &= ~(1 << DDA0) & ~(1 << DDA1);
}

void gererEtatAppui2(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::ALLUME;
    }
    PORTA &= ~(1 << DDA0) & ~(1 << DDA1);
}

void gererEtatAllume(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::INIT;
    }
    PORTA |= 1 << DDA1;
}

int main() {
    // Inspiré par le code d'un des chargés sur le TP1 (pour set les modes des pins et pour lire les pins)

    DDRA |= (1 << DDA0) | (1 << DDA1);

    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);

    Etat etatPresent = Etat::INIT;

    while (true) {
        if (verifierAppuiBouton(PIND, PIND3)) {
            etatPresent = Etat::INIT;
        }

        switch (etatPresent) {
            case Etat::INIT:
                gererEtatInit(etatPresent);
                break;
            case Etat::APPUI_1:
                gererEtatAppui1(etatPresent);
                break;
            case Etat::APPUI_2:
                gererEtatAppui2(etatPresent);
                break;
            case Etat::ALLUME:
                gererEtatAllume(etatPresent);
                break;
        }
    }

    return 0;
}