#define F_CPU 8000000L

#include "ButtonPressDetector.h"

#include <util/delay.h>

void ButtonPressDetector::init() {
    DDRD &= ~((1 << DDD2) | (1 << DDD3));

}

bool ButtonPressDetector::isBreadButtonPressed() {
    bool pressed = ~PIND & (1 << DDD3);

    if (pressed) {
        _delay_ms(DEBOUNCE_TIME);
        return ~PIND & (1 << DDD3);
    }
    return false;
}

bool ButtonPressDetector::isSmallButtonPressed() {
    bool pressed = PIND & (1 << DDD2);

    if (pressed) {
        _delay_ms(DEBOUNCE_TIME);
        return PIND & (1 << DDD2);
    }
    return false;
}
