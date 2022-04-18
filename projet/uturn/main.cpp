#define F_CPU 8000000
#include <can.h>
#include <MotorsController.h>
#include <usart.h>
#include <DistanceSensor.h>
#include <WallFollower.h>
#include <util/delay.h>

int main() {
    MotorsController::initialization();
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(80);
    MotorsController::setRightPercentage(80);
    _delay_ms(400);
    MotorsController::setRightPercentage(60);


}