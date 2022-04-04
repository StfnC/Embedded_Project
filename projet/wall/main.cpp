#include <can.h>
#include <MotorsController.h>
#include <usart.h>
#include <DistanceSensor.h>

// FIXME: -Transform this into a class
//        -Create state machine to handle the different cases

const uint8_t ADC_POSITION = 2;
const uint8_t PRECISION_LOSS = 2;

// FIXME: Only for testing, will need to change
const uint8_t FOLLOWING_DISTANCE_THRESHOLD = 71;
const uint8_t FOLLOWING_DISTANCE_ERROR = 5;
const uint8_t MOTOR_MULTIPLIER = 3;

void initialization() {
    DDRA &= ~(1 << ADC_POSITION);
}

bool isTooFarFromWall(uint8_t distance) {
    return (distance < FOLLOWING_DISTANCE_THRESHOLD - FOLLOWING_DISTANCE_ERROR);
}

bool isTooCloseFromWall(uint8_t distance) {
    return (distance > FOLLOWING_DISTANCE_THRESHOLD + FOLLOWING_DISTANCE_ERROR);
}

void creepCloser() {
    MotorsController::setLeftPercentage(0);
    MotorsController::setRightPercentage(0);
}

void backAway() {
    MotorsController::setLeftPercentage(0);
    MotorsController::setRightPercentage(0);
}

void goStraight() {
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(100);
    MotorsController::setRightPercentage(100);
}

int main() {
    MotorsController::initialization();
    usart::initialization();
    uint8_t analogReading;

    while (true) {
        analogReading = DistanceSensor::getDistance();
        usart::transmitTextMessage("Analog Reading : %d\n", analogReading);

        if (isTooFarFromWall(analogReading)) {
            usart::transmitTextMessage("Too far\n");
            creepCloser();
        } else if (isTooCloseFromWall(analogReading)) {
            usart::transmitTextMessage("Too close\n");
            backAway();
        } else {
            usart::transmitTextMessage("Right distance\n");
            goStraight();
        }
    }

    return 0;
}