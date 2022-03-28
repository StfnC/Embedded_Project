#include <can.h>
#include <usart.h>

int main() {
    DDRA = 0x00;
    can conv = can();
    usart tr = usart();
    uint8_t lecture;

    while (true) {
        lecture = static_cast<uint8_t>(conv.lecture(1) >> 2);
        tr.transmit(lecture);
    }
}