#include <avr/io.h>

#include "State.h"

class Robot {
    public:
        static void init();

        static void run();

    private:
        static State currentState_;

        static void manageStateMachine();
        static void manageStateInit();
        static void manageStateStartRerun();
        static void manageStateRerun();
        static void manageStateEndRerun();
        static void manageStateStartAutonomous();
        static void manageStateStartMemorizing();
        static void manageStateFollowWall();
        static void manageStateFollowLight();
        static void manageStateStopMemorizing();
        static void manageStateStartUTurn();
        static void manageStateUTurn();
        static void manageStateEndAutonomous();

};
