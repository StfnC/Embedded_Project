#include <avr/io.h>
#include <counter.h>
#include <debug.h>
#include <memoire_24.h>

Memoire24CXXX memoire;

ISR(TIMER1_COMPA_vect) {

}

int main() {
    DEBUG_INIT;
    
}

