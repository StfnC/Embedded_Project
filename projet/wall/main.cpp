#include <can.h>
#include <usart.h>

const uint8_t ADC_POSITION = 2;
const uint8_t PRECISION_LOSS = 2;

void initialization() {
    DDRA &= ~(1 << ADC_POSITION);
}

int main() {
    can can;
    usart usart;
    uint8_t analogReading;

    while (true) {
        analogReading = static_cast<uint8_t>(can.lecture(ADC_POSITION) >> PRECISION_LOSS);
        usart.transmitTextMessage("Analog Reading : %d\n", analogReading);
    }
    
    return 0;
}