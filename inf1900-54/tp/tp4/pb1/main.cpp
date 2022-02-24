#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 8000000
#include <util/delay.h>

static const uint8_t RED = 0x02;
static const uint8_t GREEN = 0x01;
static const uint8_t OFF = 0x00;

enum class State
{
    INIT,
    CLIC1,
    CLIC2
};

void changeState(volatile State& machine, State nextState);
void setColor(uint8_t color);
volatile State machine = State::INIT;

void initialisation(void)
{

    cli();

    DDRA = 0xff;
    DDRD = 0x00;

    EIMSK |= (1 << INT0) | (1 << INT1);

    EICRA |= (ISC00 << 1 ) | (ISC01 << 1) | (ISC10 << 1 ) | (ISC11 << 1);


    sei();
}

ISR(INT0_vect)
{
    _delay_ms(30);

    
    switch (machine)
    {
    case State::INIT:
        machine = State::CLIC1;
        break;

    case State::CLIC1:
        machine = State::INIT;
        break;

    case State::CLIC2:
        machine = State::CLIC1;
        break;
    }
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(30);
    switch (machine)
    {
    case State::INIT:
        machine = State::CLIC1;
        break;

    case State::CLIC1:
        machine = State::CLIC2;
        break;

    case State::CLIC2:
        machine = State::INIT;
        break;
    }
    EIFR |= (1 << INTF0);
}

void setColor(uint8_t color)
{
    PORTA = color;
}

int main()
{
    initialisation();
    while (true)
    {
        switch (machine)
        {
        case State::INIT:
            setColor(RED);
            break;

        case State::CLIC1:
            setColor(GREEN);
            break;

        case State::CLIC2:
            setColor(OFF);
            break;
        }
    }
}