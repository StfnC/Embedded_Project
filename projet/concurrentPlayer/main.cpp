#define F_CPU 8000000UL

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
    SystemTimer::init();
    BuzzerController::initBuzzer();
    ConcurrentMusicPlayer::init();

    while (true) {
        ConcurrentMusicPlayer::playMusic();
    }
    
    return 0;
}