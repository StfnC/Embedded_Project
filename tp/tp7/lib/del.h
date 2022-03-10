#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

class del
{
	public:
	   del(uint8_t port,uint8_t pin1, uint8_t pin2);
	   ~del(uint8_t port,uint8_t pin1, uint8_t pin2);
	   
	   void delGreen();
	   void delRed();
	   void delOff();
	   void delYellow();

	private:
	   uint8_t port;
	   uint8_t pin1;
	   uint8_t pin2;
};
