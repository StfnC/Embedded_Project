/**
 * Problème 2 du TP2
 * Ce code implémente la machine à états du 2e problème du TP2.
 * La machine est implémentée en Moore et présente 3 états.
 * 
 * \file pb2.cpp
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
#include <avr/io.h>
#include <util/delay.h>
#include <debug.h>

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
        return port & (1 << pin);
    }
    return false;
}

void gererEtatAllumeRouge(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2) || verifierAppuiBouton(PIND, PIND3)) {
        etatPresent = Etat::ALLUME_VERT;
    }

    PORTA &= ~(1 << DDA0);
    PORTA |= 1 << DDA1;
}

void gererEtatAllumeVert(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::ALLUME_ROUGE;
    } else if (verifierAppuiBouton(PIND, PIND3)) {
        etatPresent = Etat::ETEINT;
    }

    PORTA |= 1 << DDA0;
    PORTA &= ~(1 << DDA1);
}

void gererEtatEteint(Etat& etatPresent) {
    if (verifierAppuiBouton(PIND, PIND2)) {
        etatPresent = Etat::ALLUME_VERT;
    } else if (verifierAppuiBouton(PIND, PIND3)) {
        etatPresent = Etat::ALLUME_ROUGE;
    }

    PORTA &= ~(1 << DDA0) & ~(1 << DDA1);
}

int main() {
    DEBUG_INIT;
    uint8_t msgEtatAllumeRouge[] = "STATE: ALLUME_ROUGE\n";
    uint8_t msgEtatAllumeVert[] = "STATE: ALLUME_VERT\n";
    uint8_t msgEtatEteint[] = "STATE: ETEINT\n";
    // Inspiré par le code d'un des chargés sur le TP1 (pour set les modes des pins et pour lire les pins)

    DDRA |= (1 << DDA0) | (1 << DDA1);

    DDRD &= ~(1 << DDD2) & ~(1 << DDD3);

    Etat etatPresent = Etat::ALLUME_ROUGE;

    while (true) {
        switch (etatPresent) {
            case Etat::ALLUME_ROUGE:
                DEBUG_PRINT_MESSAGE(msgEtatAllumeRouge, 21);
                gererEtatAllumeRouge(etatPresent);
                break;
            case Etat::ALLUME_VERT:
                DEBUG_PRINT_MESSAGE(msgEtatAllumeVert, 20);
                gererEtatAllumeVert(etatPresent);
                break;
            case Etat::ETEINT:
                DEBUG_PRINT_MESSAGE(msgEtatEteint, 15);
                gererEtatEteint(etatPresent);
                break;
        }
    }

    return 0;
}