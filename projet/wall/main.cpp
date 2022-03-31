#include <can.h>
#include <MotorsController.h>
#include <usart.h>

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

void creepCloser(MotorsController& motors) {
    motors.setLeftPercentage(0);
    motors.setRightPercentage(0);
}

void backAway(MotorsController& motors) {
    motors.setLeftPercentage(0);
    motors.setRightPercentage(0);
}

void goStraight(MotorsController& motors) {
    motors.changeLeftDirection(Direction::Forward);
    motors.changeRightDirection(Direction::Forward);
    motors.setLeftPercentage(100);
    motors.setRightPercentage(100);
}

int main() {
    can can;
    usart usart;
    uint8_t analogReading;
    MotorsController motors;

    while (true) {
        analogReading = static_cast<uint8_t>(can.lecture(ADC_POSITION) >> PRECISION_LOSS);
        usart.transmitTextMessage("Analog Reading : %d\n", analogReading);

        if (isTooFarFromWall(analogReading)) {
            usart.transmitTextMessage("Too far\n");
            creepCloser(motors);
        } else if (isTooCloseFromWall(analogReading)) {
            usart.transmitTextMessage("Too close\n");
            backAway(motors);
        } else {
            usart.transmitTextMessage("Right distance\n");
            goStraight(motors);
        }
    }

    return 0;
}