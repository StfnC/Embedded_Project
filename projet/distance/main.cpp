#define F_CPU 8000000L

#include <DistanceSensor.h>
#include <usart.h>

int main() {
    usart::initialization();
    DistanceSensor::initialization();

    while (true){
        usart::transmitTextMessage("%d\n", DistanceSensor::getDistanceCm());
    }
}