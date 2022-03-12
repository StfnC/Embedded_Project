#define F_CPU 8000000

#include <avr/io.h>
#include <led.h>

// FIXME: Write headers for all files, don't forget the pinout

int main() {
    DDRA |= (1 << DDA0) | (1 << DDA1);

    led del0(&PORTA, DDA0, DDA1);

    uint16_t count = 0;

    while (count < 65000) {
        del0.setGreen();
        count++;
    }

    del0.setOff();

    return 0;
}