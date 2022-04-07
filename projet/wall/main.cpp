#include <can.h>
#include <MotorsController.h>
#include <usart.h>
#include <DistanceSensor.h>
#include <WallFollower.h>


int main() {
    DistanceSensor::initialization();
    MotorsController::initialization();
    usart::initialization();

    while (true) {
        WallFollower::followWall();
    }

    return 0;
}