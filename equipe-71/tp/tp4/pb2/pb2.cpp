#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t TEMPS_DEBOUNCE = 10;
volatile bool gMinuterieExpiree;
volatile bool gBoutonPoussoir;

ISR(TIMER1_COMPA_vect) {
    gMinuterieExpiree = true;
}

ISR(INT0_vect) {
    gBoutonPoussoir = true;

    _delay_ms(TEMPS_DEBOUNCE);

    if (!(PIND & (1 << PIND2))) {
        gBoutonPoussoir = false;
    }
}

void initialisation() {
    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontrôleur n'est pas prêt...

    cli();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD &= ~(1 << DDD2);

    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0);

    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei();
}

void partirMinuterie(uint16_t duree) {
    gMinuterieExpiree = false;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    // On peut laisser TCCR1A a zero, car on n'utilise pas les pins OCnA ou OCnB
    TCCR1A = 0;

    // Prescaler de 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A);
}

int main() {
    initialisation();

    // Delai d'attente maximum, pour 10s il faudrait 78124 (nCycles = Delai * Freq / Prescaler - 1), base sur https://maxembedded.com/2011/06/introduction-to-avr-timers/
    partirMinuterie(65534);

    do {
    } while (!gMinuterieExpiree);

    // Delai pour faire clignoter la DEL
    partirMinuterie(780);

    do {
        PORTA |= (1 << DDA1);
    } while (!gMinuterieExpiree);

    PORTA &= ~(1 << DDA1) | (1 << DDA0);

    partirMinuterie(7812);

    do {
        // attendre qu'une des deux variables soit modifiée

        // par une ou l'autre des interruptions.

    } while (!gMinuterieExpiree && !gBoutonPoussoir);

    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli();

    // Verifier la réponse

    if (gBoutonPoussoir && !gMinuterieExpiree) {
        PORTA |= (1 << DDA0);
    } else {
        PORTA |= (1 << DDA1);
    }

    return 0;
}