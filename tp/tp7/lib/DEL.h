#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

class DEL
{
	public:
	   LED(uint8_t port,uint8_t pin1, uint8_t pin2);
	   ~LED(uint8_t port,uint8_t pin1, uint8_t pin2);
	   
	   void DEL_GREEN();
	   void DEL_RED();
	   void DEL_OFF();
	   void DEL_YELLOW();

	private:
	   uint8_t port;
	   uint8_t pin1;
	   uint8_t pin2;
};
