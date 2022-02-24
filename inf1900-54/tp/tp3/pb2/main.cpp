
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main() 
{
    DDRB = 0xff;
    DDRA = 0xff;
    //Pour 60Hz
    double nombreDelayB = 33333;
    double duree2Sec = 120;
    double nombreDelayA = 0;
    double nombreDelayP = 0;
    double taux = 0;

    // PORTB = 0xFF;
    for (int j = 0; j < 2; j++)
     {
         if (j==1)
         {
             nombreDelayB = 500;
             duree2Sec = 800;
         }
         for (int iterator = 0; iterator < 4; iterator++)
         {
              if (iterator == 0 )
              {
                  taux = 0;
              }
              else if (iterator == 1)
              {
                  taux = 0.5 ;
              }
              else if (iterator == 2)
              {
                  taux = 0.75 ;
              }
              else if (iterator == 3)
              {
                  taux = 1 ;
              }
            nombreDelayA = taux * nombreDelayB;
            nombreDelayP = nombreDelayB - nombreDelayA;
             for (int i = 0; i < duree2Sec; i++)
             {
                 PORTB = 0x01;
                 if (nombreDelayA != 0)
                 {
                 _delay_loop_2(nombreDelayA);
                 }
                 PORTB = 0x00;
                 if (nombreDelayP != 0)
                 {
                 _delay_loop_2(nombreDelayP);
                 }
             }
             
        }       
     }
}