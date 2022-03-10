#include <avr/io.h>

class usart {
    public:
        usart();
        
        ~usart();

        void transmit(uint8_t data);

        uint8_t receive(void);

        void transmitTextMessage(uint8_t message[], uint8_t messageLength);
    private:
        void initialization(void);

};
