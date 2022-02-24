#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000
#include <util/delay.h>

volatile uint8_t gMinutrieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;
volatile uint8_t color;

const uint8_t RED = 0X02;
const uint8_t GREEN = 0X01;
const uint8_t OFF = 0X00;

void setColor(uint8_t color)
{
    PORTA = color;
}

void initialisation(void)
{

    cli();

    DDRA = 0xff;
    DDRD = 0x00;

    EIMSK |= (1 << INT0) ;

    EICRA = (1 << ISC00) | (1 << ISC01);


    sei();
}

ISR(TIMER1_COMPA_vect)
{
    gMinutrieExpiree = 1;
}

ISR(INT0_vect)
{
    gBoutonPoussoir = 1;

}

void partirMinuterie(uint16_t duree)
{

    gMinutrieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0x0;

    OCR1A = duree;

    TCCR1A = 0;

    TCCR1B = (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

int main()
{
    initialisation();
    setColor(RED);
    _delay_ms(100);
    setColor(OFF);
    gBoutonPoussoir = 0;

    partirMinuterie(7813 * 4);
    while (!gMinutrieExpiree && !gBoutonPoussoir){}

    cli();

    if (gMinutrieExpiree)
    {
        setColor(RED);
    }
    else if (gBoutonPoussoir)
    {
        setColor(GREEN);
    }
}

