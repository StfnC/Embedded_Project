#include <avr/io.h>

#include "State.h"

class Robot {
    public:
        static void init();

        static void run();

    private:
        static State currentState_;
};
