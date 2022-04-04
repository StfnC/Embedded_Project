#include "DistanceSensor.h"

// FIXME: Make sure this pin is in read-mode
const uint8_t DistanceSensor::PIN_ = 2;

can DistanceSensor::can_;

uint8_t DistanceSensor::getDistance() {
    return getVoltage();
}

void DistanceSensor::calibrate() {
}

uint8_t DistanceSensor::getVoltage() {
    // FIXME: Don't hard-code the >> 2, maybe create a method in can to get the reading on 8 bits
    return static_cast<uint8_t>(can_.lecture(PIN_) >> 2);
}
