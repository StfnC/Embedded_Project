#include "DistanceSensor.h"

// FIXME: Make sure this pin is in read-mode
const uint8_t DistanceSensor::PIN_ = 2;

can DistanceSensor::can_;

void DistanceSensor::initialization() {
    DDRA &= ~(1 << PIN_);
    calibrate();
}

uint8_t DistanceSensor::getDistance() {
    return getVoltage();
}

void DistanceSensor::calibrate() {
}

uint8_t DistanceSensor::getVoltage() {
    return can_.lecture8Bits(PIN_);
}
