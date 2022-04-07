#pragma once

#include "DistanceSensor.h"
#include "MotorsController.h"

class WallFollower {
    // FIXME: Maybe create an enum for the state of the wall following

    public:
        static void followWall();

    private:
        static const uint8_t FOLLOWING_DISTANCE_THRESHOLD;
        static const uint8_t FOLLOWING_DISTANCE_ERROR;

        static void goStraight();
        static void getCloser();
        static void getAway();
};
