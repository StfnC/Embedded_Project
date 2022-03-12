#define F_CPU 8000000

#include <avr/io.h>
#include <led.h>

int main() {
    DDRA |= (1 << DDA0) | (1 << DDA1);

    led del0(&PORTA, DDA0, DDA1);

    while (true) {
        del0.setYellow();
    }

    return 0;
}