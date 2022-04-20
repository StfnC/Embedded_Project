#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include <avr/interrupt.h>
#include <debug.h>
#include <SystemTimer.h>
#include <ConcurrentMusicPlayer.h>
#include <util/delay.h>

ISR(TIMER2_COMPA_vect) {
    SystemTimer::incrementTimer();
}

int main() {
    DEBUG_INIT;
    BuzzerController::initBuzzer();
    ConcurrentMusicPlayer::interpretCode();
    return 0;
}