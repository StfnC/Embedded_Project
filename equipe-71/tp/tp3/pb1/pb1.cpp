/**
  * \file pb1.cpp
 * \author Stefan Cotargasanu et Justine Sauquet
 * \date 27 Janvier 2022
 * 
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main() {
    const uint16_t PERIODE = 1000;  // En micro-secondes
    const uint8_t COEFFICIENT_DELAI = 50;

    DDRB |= (1 << DDB0) | (1 << DDB1);

    uint16_t tempsAllume = PERIODE;
    uint16_t tempsEteint = 0;

    while (true) {
        PORTB |= 1 << PORTB0;

        for (uint16_t iteration = 3000; iteration > 0; iteration--) {
            for (uint16_t i = 0; i < (tempsAllume / COEFFICIENT_DELAI); i++) {
                _delay_us(COEFFICIENT_DELAI);
            }

            PORTB &= ~(1 << PORTB0);

            for (uint16_t i = 0; i < (tempsEteint / COEFFICIENT_DELAI); i++) {
                _delay_us(COEFFICIENT_DELAI);
            }

            if (tempsAllume >= 0 && tempsEteint <= PERIODE) {
                tempsAllume -= COEFFICIENT_DELAI;
                tempsEteint += COEFFICIENT_DELAI;
            } else {
                tempsAllume = PERIODE;
                tempsEteint = 0;
            }
        }
    }

    return 0;
}