#define F_CPU 8000000

#include <avr/io.h>
#include <del.h>

int main() {
    DDRA |= (1 << DDA0) | (1 << DDA1);

    del del0(&PORTA, DDA0, DDA1);

    while (true) {
        del0.delGreen();
    }

    return 0;
}