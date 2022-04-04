#include "DistanceSensor.h"

const uint8_t DistanceSensor::PIN_ = 2;

can DistanceSensor::can_;

uint8_t DistanceSensor::getDistance() {
    return 0;
}

void DistanceSensor::calibrate() {
}

uint8_t DistanceSensor::getVoltage() {
    return 0;
}
