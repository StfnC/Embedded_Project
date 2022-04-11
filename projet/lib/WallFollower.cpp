#include "WallFollower.h"
#include "usart.h"

// FIXME: Get rid of hardcoded values

const uint8_t WallFollower::FOLLOWING_DISTANCE_THRESHOLD = 71;
const uint8_t WallFollower::FOLLOWING_DISTANCE_ERROR = 5;
const uint8_t WallFollower::NO_WALL_THRESHOLD = 30;


void WallFollower::followWall() {
    uint8_t distance = DistanceSensor::getDistanceCm();

    usart::transmitTextMessage("Distance : %d\n", distance);

    // FIXME: Create an enum for the different distances
    if (distance < NO_WALL_THRESHOLD) {
        fullStop();
    } else if (distance > WallFollower::FOLLOWING_DISTANCE_THRESHOLD + WallFollower::FOLLOWING_DISTANCE_ERROR) {
        getAway();
    } else if (distance < WallFollower::FOLLOWING_DISTANCE_THRESHOLD - WallFollower::FOLLOWING_DISTANCE_ERROR) {
        getCloser();
    } else {
        goStraight();
    }
}

void WallFollower::goStraight() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(85);
    MotorsController::setRightPercentage(75);
}

void WallFollower::getCloser() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(75);
    MotorsController::setRightPercentage(50);
}

void WallFollower::getAway() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(50);
    MotorsController::setRightPercentage(70);
}

void WallFollower::fullStop() {
    MotorsController::setRightPercentage(0);
    MotorsController::setLeftPercentage(0);
}