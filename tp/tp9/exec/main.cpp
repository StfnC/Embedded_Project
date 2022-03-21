#define F_CPU 8000000

#include <debug.h>
#include <led.h>
#include <memoire_24.h>
#include <usart.h>
#include <util/delay.h>
#include <Partition.h>

#include "RobotProgramDownloader.h"

int main() {
   
   DDRA = 0XFF;
   DDRB = 0XFF;
   DDRD = 0XFF;

    Partition::partition();

    
    return 0;
}