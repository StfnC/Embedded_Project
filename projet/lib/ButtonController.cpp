#include "ButtonController.h"

bool ButtonController::breadButtonPressed_ = false;
bool ButtonController::smallButtonPressed_ = false;

void ButtonController::init() {

}

bool ButtonController::isBreadButtonPressed() {
    return breadButtonPressed_;
}

bool ButtonController::isSmallButtonPressed() {
    return smallButtonPressed_;
}

void ButtonController::setBreadButtonPressed(bool pressed) {
    breadButtonPressed_ = pressed;
}

void ButtonController::setSmallButtonPressed(bool pressed) {
    smallButtonPressed_ = pressed;
}
