#include <avr/io.h>

class BuzzerController {
    public:
        static void initBuzzer();
        static void playNote(uint8_t note);
        static void stopNote();
};