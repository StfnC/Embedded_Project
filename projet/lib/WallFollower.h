#pragma once

#include "DistanceSensor.h"
#include "MotorsController.h"

class WallFollower {
    public:
        static void followWall();
        static bool isWallDetected();

    private:
        static constexpr uint8_t FOLLOWING_DISTANCE_THRESHOLD = 20;
        static constexpr uint8_t FOLLOWING_DISTANCE_ERROR = 1;
        static constexpr uint8_t NO_WALL_THRESHOLD = 40;
        static constexpr uint8_t BASE_SPEED = 40;
        static constexpr uint8_t DIFFERENCE_WHEELS = 15;

        static uint8_t distance_;
        static bool wallDetected_;

        static void goStraight();
        static void getCloser();
        static void getAway();
        static void fullStop();
};
