#include <avr/io.h>

class SystemTimer {
    public:
        static void init();
        static void start();
        static void stop();
        static void incrementTimer();
        static inline uint16_t getTimer() {
            return timerCount_;
        }

    private:
        static const uint8_t ONE_MS_WITH_32_PRESCALER = 125;
        static uint32_t timerCount_;
};
