#include "WallFollower.h"
#include "usart.h"

// FIXME: Get rid of hardcoded values

const uint8_t WallFollower::FOLLOWING_DISTANCE_THRESHOLD = 71;
const uint8_t WallFollower::FOLLOWING_DISTANCE_ERROR = 5;

void WallFollower::followWall() {
    uint8_t distance = DistanceSensor::getDistance();

    usart::transmitTextMessage("Distance : %d\n", distance);

    // FIXME: Create an enum for the different distances
    if (distance < WallFollower::FOLLOWING_DISTANCE_THRESHOLD - WallFollower::FOLLOWING_DISTANCE_ERROR) {
        getCloser();
    } else if (distance > WallFollower::FOLLOWING_DISTANCE_THRESHOLD + WallFollower::FOLLOWING_DISTANCE_ERROR) {
        getAway();
    } else {
        goStraight();
    }
}

void WallFollower::goStraight() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(75);
    MotorsController::setRightPercentage(75);
}

void WallFollower::getCloser() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(100);
    MotorsController::setRightPercentage(75);
}

void WallFollower::getAway() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(75);
    MotorsController::setRightPercentage(100);
}