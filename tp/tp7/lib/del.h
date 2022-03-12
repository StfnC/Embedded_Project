#include <avr/io.h>

class del
{
	public:
	   del(volatile uint8_t* port,uint8_t pin1, uint8_t pin2);
	   ~del();
	   
	   void delGreen();
	   void delRed();
	   void delOff();
	   void delYellow();

	private:
	   volatile uint8_t* port_;
	   uint8_t pin1_;
	   uint8_t pin2_;
};
