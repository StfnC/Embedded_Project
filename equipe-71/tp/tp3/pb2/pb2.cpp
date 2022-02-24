/**
  * \file pb2.cpp
 * \author Stefan Cotargasanu et Justine Sauquet
 * \date 27 Janvier 2022
 * 
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRB |= (1 << DDB0) | (1 << DDB1);

    return 0;
}