#include <debug.h>
#include <MotorsController.h>

int main() {
    DEBUG_INIT;
    MotorsController::initialization();
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);

    while (true) {
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Hello Debug %d\n", 55);
        DEBUG_PRINT_MESSAGE("Hello Debug Message\n");
        MotorsController::setLeftPercentage(100);
        MotorsController::setRightPercentage(100);
    }
    
    return 0;
}