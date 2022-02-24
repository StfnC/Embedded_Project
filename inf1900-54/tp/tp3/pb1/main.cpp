


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
    DDRA = 0xff;
    DDRB = 0xff;
    const int nombreDelayLoopDeB = 2000;
    int nombreDelayLoopDeA = 2000;
    int nombreDelayLoopDeP = 0;
    double taux = 1;
    int j = 0;
    uint8_t color = 0;
    while (true)
    {
        taux = 1;
        int i = 0;
        if (j % 2 == 0)
        {
            color = 0x01;
        }
        else {
            color = 0x02;
        }
        while (taux > 0)
        {
            nombreDelayLoopDeA = taux * nombreDelayLoopDeB;
            nombreDelayLoopDeP = nombreDelayLoopDeB - nombreDelayLoopDeA;

            PORTA = color;
            PORTB = 0x01;
            if (nombreDelayLoopDeA != 0 )
            {
            _delay_loop_2(nombreDelayLoopDeA); 
            }
            
            PORTA = 0x00;  
            PORTB = 0x00;
            if (nombreDelayLoopDeP != 0 )
            {
            _delay_loop_2(nombreDelayLoopDeP);
            }

            if (i % 30 == 0)
            {
                taux -= 0.01;
            }
            i++;
        }
    j++;
    }
}