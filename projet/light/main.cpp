
#include <stdio.h>
#include <can.h>
#include <usart.h>
#include <debug.h>

uint8_t ambiantLightCalculation(can& conv, usart& tr);

int main() {
    DEBUG_INIT;
    DDRA = 0x00;
    DDRB = 0X00;
    can conv = can();
    usart tr = usart();
    uint8_t lectureg;
    uint8_t lectured;

    uint8_t average = ambiantLightCalculation(conv, tr);
    DEBUG_PRINT_MESSAGE_WITH_VALUE("La luminosite est de : %d", average);

    while (true) {
        uint8_t leftValue = static_cast<uint8_t>(conv.lecture(1) >> 2);
        uint8_t rightValue = static_cast<uint8_t>(conv.lecture(3) >> 2);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("Gauche : %d", leftValue);
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tDroite : %d", rightValue);
        uint8_t difference = rightValue - leftValue;
        DEBUG_PRINT_MESSAGE_WITH_VALUE("\tDifference : %d\n", difference);
    }
}

uint8_t ambiantLightCalculation(can& conv, usart& tr) {
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