#include <can.h>
#include <MotorsController.h>
#include <usart.h>
#include <DistanceSensor.h>
#include <WallFollower.h>


int main() {
    usart::initialization();
    DistanceSensor::initialization();
    MotorsController::initialization();

    while (true) {
        WallFollower::followWall();
    }

    return 0;
}