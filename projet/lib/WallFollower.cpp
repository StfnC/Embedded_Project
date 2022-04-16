#include "WallFollower.h"

#include "usart.h"

const uint8_t WallFollower::FOLLOWING_DISTANCE_THRESHOLD = 20;
const uint8_t WallFollower::FOLLOWING_DISTANCE_ERROR = 1;
const uint8_t WallFollower::NO_WALL_THRESHOLD = 50;
const uint8_t WallFollower::BASE_SPEED = 40;

uint8_t WallFollower::distance_;

void WallFollower::followWall() {
    distance_ = DistanceSensor::getDistanceCm();

    usart::transmitTextMessage("Distance : %d\n", distance_);

    // FIXME: Create an enum for the different distances
    if (distance_ > NO_WALL_THRESHOLD) {
        wallDetected_ = false;
        fullStop();
    } else if (distance_ < WallFollower::FOLLOWING_DISTANCE_THRESHOLD - WallFollower::FOLLOWING_DISTANCE_ERROR) {
        wallDetected_ = true;
        getAway();
    } else if (distance_ > WallFollower::FOLLOWING_DISTANCE_THRESHOLD + WallFollower::FOLLOWING_DISTANCE_ERROR) {
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
    MotorsController::setLeftPercentage(BASE_SPEED + 15);
    MotorsController::setRightPercentage(BASE_SPEED - 15);
}

void WallFollower::getAway() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(BASE_SPEED - 15);
    MotorsController::setRightPercentage(BASE_SPEED + 15);
}

void WallFollower::fullStop() {
    MotorsController::setRightPercentage(0);
    MotorsController::setLeftPercentage(0);
}

bool WallFollower::isWallDetected() {
    return wallDetected_;
}
