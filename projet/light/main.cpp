#include <stdio.h>
#include <can.h>
#include <usart.h>
#include <debug.h>
#include <util/delay.h>
#include <MotorsController.h>
uint8_t ambientLightCalculation(can& conv, usart& tr);
void waitForCenter(uint8_t average);
can conv = can();
int main() {
    MotorsController::initialization();
    DEBUG_INIT;
    DDRA = 0x00;
    DDRB = 0xff;
    usart tr = usart();
    uint8_t lectureg;
    uint8_t lectured;
    uint8_t average = ambientLightCalculation(conv, tr);
    tr.transmitTextMessage("La luminosite est de : %d \n", average);
    while (true) {
        uint8_t leftValue = static_cast<uint8_t>(conv.lecture(3) >> 2);
        uint8_t rightValue = static_cast<uint8_t>(conv.lecture(1) >> 2);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Gauche : %d", leftValue);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tDroite : %d", rightValue);
        uint8_t difference = rightValue - leftValue;
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tDifference gauche droite : %d", difference);
        uint8_t midValue = leftValue - rightValue + 128;
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tMidValue : %d\n", midValue);
        if (leftValue >= average + 20 || rightValue >= average + 20) {
            waitForCenter(average);
        }
        MotorsController::setLeftPercentage(0);
        MotorsController::setRightPercentage(0);
    }
}
uint8_t ambientLightCalculation(can& conv, usart& tr) {
    uint8_t leftValue;
    uint8_t rightValue;
    uint16_t average = 0;
    for (int i = 0; i < 10000; i++)
    {
        leftValue = static_cast<uint8_t>(conv.lecture(1) >> 2);
        rightValue = static_cast<uint8_t>(conv.lecture(5) >> 2);
        average += (leftValue + rightValue) / 2;
        if (i > 1) {
            average = average / 2;
        }
    }
    return static_cast<uint8_t>(average);
}
void waitForCenter(uint8_t average) {
    bool centered = false;
    DEBUG_PRINT_MESSAGE("lolilololol\n");
    uint8_t leftValue = static_cast<uint8_t>(conv.lecture(3) >> 2);
    uint8_t rightValue = static_cast<uint8_t>(conv.lecture(1) >> 2);
    // while (!(centered) || leftValue >= average + 20 || rightValue >= average + 20) {
    while ((leftValue >= (average + 20)) || (rightValue >= (average + 20))) {
        DEBUG_PRINT_MESSAGE_WITH_VALUE("%d", average);
        leftValue = static_cast<uint8_t>(conv.lecture(3) >> 2);
        rightValue = static_cast<uint8_t>(conv.lecture(1) >> 2);
        uint8_t midValue = leftValue - rightValue + 128;
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Gauche : %d", leftValue);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tDroite : %d", rightValue);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tMidValue : %d\n", midValue);
        if (midValue >= 138) {
            MotorsController::setLeftPercentage(90);
            MotorsController::setRightPercentage(90);
            MotorsController::changeLeftDirection(Direction::Reverse);
            MotorsController::changeRightDirection(Direction::Forward);
        }
        else if (midValue <= 122) {
            MotorsController::setLeftPercentage(90);
            MotorsController::setRightPercentage(90);
            MotorsController::changeLeftDirection(Direction::Forward);
            MotorsController::changeRightDirection(Direction::Reverse);
        }
        else {
            MotorsController::setLeftPower(rightValue);
            MotorsController::setRightPower(leftValue);
            MotorsController::changeLeftDirection(Direction::Forward);
            MotorsController::changeRightDirection(Direction::Forward);
        }
        // if (midValue <= 129 && midValue >= 127) {
        //     DEBUG_PRINT_MESSAGE("CACA\n");
        //     centered = true;
        // }
    }
    DEBUG_PRINT_MESSAGE("\t\t\t\t zezette \n\n\n\n");
}