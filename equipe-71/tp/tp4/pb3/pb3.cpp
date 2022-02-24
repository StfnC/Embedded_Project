#define F_CPU 8000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t ZERO_POURCENT = 255; // 255, car tourne un peu a 0
const uint8_t VINGT_CINQ_POURCENT = 64; // 255, car tourne un peu a 0
const uint8_t CINQUANTE_POURCENT = 128; // 255, car tourne un peu a 0
const uint8_t SOIXANTE_QUINZE_POURCENT = 192; // 255, car tourne un peu a 0
const uint8_t CENT_POURCENT = 254; // 255, car tourne un peu a 0


void initialisation() {
    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontrôleur n'est pas prêt...

    cli();

    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables
    DDRD |= (1 << DDD4) | (1 << DDD5);

    sei();
}

void ajustementPwm(uint8_t thresholdPwm1, uint8_t thresholdPwm2) {
    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = thresholdPwm1;

    OCR1B = thresholdPwm2;

    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);

    TCCR1B |= (1 << CS11);

    TCCR1C = 0;
}

int main() {
    initialisation();

    ajustementPwm(ZERO_POURCENT, ZERO_POURCENT);
    _delay_ms(2000);
    ajustementPwm(VINGT_CINQ_POURCENT, VINGT_CINQ_POURCENT);
    _delay_ms(2000);
    ajustementPwm(CINQUANTE_POURCENT, CINQUANTE_POURCENT);
    _delay_ms(2000);
    ajustementPwm(SOIXANTE_QUINZE_POURCENT, SOIXANTE_QUINZE_POURCENT);
    _delay_ms(2000);
    ajustementPwm(CENT_POURCENT, CENT_POURCENT);
    _delay_ms(2000);
    ajustementPwm(CENT_POURCENT, CENT_POURCENT);
    _delay_ms(2000);
    ajustementPwm(SOIXANTE_QUINZE_POURCENT, SOIXANTE_QUINZE_POURCENT);
    _delay_ms(2000);
    ajustementPwm(CINQUANTE_POURCENT, CINQUANTE_POURCENT);
    _delay_ms(2000);
    ajustementPwm(VINGT_CINQ_POURCENT, VINGT_CINQ_POURCENT);
    _delay_ms(2000);
    ajustementPwm(ZERO_POURCENT, ZERO_POURCENT);

    return 0;
}