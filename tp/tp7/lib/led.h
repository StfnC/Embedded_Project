#include <avr/io.h>

class led
{
	public:
	   led(volatile uint8_t* port,uint8_t pin1, uint8_t pin2);
	   ~led();
	   
	   void setGreen();
	   void setRed();
	   void setOff();
	   void setYellow();

	private:
	   volatile uint8_t* port_;
	   uint8_t pin1_;
	   uint8_t pin2_;
};
