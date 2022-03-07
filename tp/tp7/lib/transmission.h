#include <avr/eeprom.h>
#define F_CPU 8000000
#include <util/delay.h>

void initialisationUART(void);
void transmissionUART(uint8_t donnee);
uint8_t USART_Receive(void);
int main();

