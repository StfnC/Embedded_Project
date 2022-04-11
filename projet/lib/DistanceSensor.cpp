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
    // Equation obtained by performing a log regression
    return static_cast<uint8_t>(pow(M_E, (222.75 - analogReading) / 44.72));
}

void DistanceSensor::calibrate() {
}

uint8_t DistanceSensor::getAnalogReading() {
    return can_.lecture8Bits(PIN_);
}
