/**
 * 
 * Implementation of the RobotProgramDownloader class
 * 
 * \file WallFollower.cpp
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 * PINOUT:
 *  Input:
 *      DistanceSensor:
 *          -A2
 *  Output:
 * 
 */


#include "WallFollower.h"

uint8_t WallFollower::distance_;
bool WallFollower::wallDetected_;

void WallFollower::followWall() {
    distance_ = DistanceSensor::getDistanceCm();

    if (distance_ > NO_WALL_THRESHOLD) {
        wallDetected_ = false;
        fullStop();
    } else if (distance_ < FOLLOWING_DISTANCE_THRESHOLD - FOLLOWING_DISTANCE_ERROR) {
        wallDetected_ = true;
        getAway();
    } else if (distance_ > FOLLOWING_DISTANCE_THRESHOLD + FOLLOWING_DISTANCE_ERROR) {
        wallDetected_ = true;
        getCloser();
    } else {
        wallDetected_ = true;
        goStraight();
    }
}

void WallFollower::goStraight() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(BASE_SPEED);
    MotorsController::setRightPercentage(BASE_SPEED);
}

void WallFollower::getCloser() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(BASE_SPEED + DIFFERENCE_WHEELS);
    MotorsController::setRightPercentage(BASE_SPEED - DIFFERENCE_WHEELS);
}

void WallFollower::getAway() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(BASE_SPEED - DIFFERENCE_WHEELS);
    MotorsController::setRightPercentage(BASE_SPEED + DIFFERENCE_WHEELS);
}

void WallFollower::fullStop() {
    MotorsController::setRightPercentage(0);
    MotorsController::setLeftPercentage(0);
}

bool WallFollower::isWallDetected() {
    return wallDetected_;
}
