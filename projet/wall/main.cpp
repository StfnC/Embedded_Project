#include <can.h>
#include <usart.h>

// FIXME: -Transform this into a class
//        -Create state machine to handle the different cases

const uint8_t ADC_POSITION = 2;
const uint8_t PRECISION_LOSS = 2;

// FIXME: Only for testing, will need to change
const uint8_t FOLLOWING_DISTANCE_THRESHOLD = 71;
const uint8_t FOLLOWING_DISTANCE_ERROR = 5;

void initialization() {
    DDRA &= ~(1 << ADC_POSITION);
}

bool isTooFarFromWall(uint8_t distance) {
    return (distance < FOLLOWING_DISTANCE_THRESHOLD - FOLLOWING_DISTANCE_ERROR);
}

bool isTooCloseFromWall(uint8_t distance) {
    return (distance > FOLLOWING_DISTANCE_THRESHOLD + FOLLOWING_DISTANCE_ERROR);
}

int main() {
    can can;
    usart usart;
    uint8_t analogReading;

    while (true) {
        analogReading = static_cast<uint8_t>(can.lecture(ADC_POSITION) >> PRECISION_LOSS);
        usart.transmitTextMessage("Analog Reading : %d\n", analogReading);

        if (isTooFarFromWall(analogReading)) {
            usart.transmitTextMessage("Too far\n");
        } else if (isTooCloseFromWall(analogReading)) {
            usart.transmitTextMessage("Too close\n");
        } else {
            usart.transmitTextMessage("Right distance\n");
        }
    }

    return 0;
}