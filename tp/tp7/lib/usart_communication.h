#include <avr/io.h>

void UsartInitialization(void);

void UsartTransmission(uint8_t data);

uint8_t UsartReception(void);

void sendTextMessage(uint8_t message[], uint8_t messageLength);