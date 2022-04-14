#include "DistanceSensor.h"

#include <math.h>

const uint8_t DistanceSensor::PIN_ = 2;

can DistanceSensor::can_;

void DistanceSensor::initialization() {
    DDRA &= ~(1 << PIN_);
    calibrate();
}

uint8_t DistanceSensor::getDistanceCm() {
    uint8_t analogReading = getAnalogReading();
    // Equation obtained by performing a power regression
    return static_cast<uint8_t>(pow(M_E, 10.03 - 1.6 * log(analogReading)));
}

void DistanceSensor::calibrate() {
}

uint8_t DistanceSensor::getAnalogReading() {
    return can_.lecture8Bits(PIN_);
}
