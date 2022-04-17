#pragma once

#include "DistanceSensor.h"
#include "MotorsController.h"

class WallFollower {
    public:
        static void followWall();
        static bool isWallDetected();

    private:
        static const uint8_t FOLLOWING_DISTANCE_THRESHOLD;
        static const uint8_t FOLLOWING_DISTANCE_ERROR;
        static const uint8_t NO_WALL_THRESHOLD;
        static const uint8_t BASE_SPEED;

        static uint8_t distance_;
        static bool wallDetected_;

        static void goStraight();
        static void getCloser();
        static void getAway();
        static void fullStop();
};
