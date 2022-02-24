/**
Program implementing a finite state machine following the following diagram.
 \file   pb1.cpp
 \author Rakotoarivony Faneva #2131367 and Lina Belloui ##2116585
 \date   january 30 2021
Created janvier 17 2022

PIN A OUT (A0 et A1 : DEL)
PIN D IN  (D2 et D3 : BUTTONS)


+--------------+----+----+---------------+--------+
| State        | D2 | D3 | Next State    | Sortie |
+--------------+----+----+---------------+--------+
| INT          | 0  | 0  | INIT          | Red    |
| INT          | 1  | X  | CLIC1         | Red    |
| INT          | 0  | 1  | CLIC1         | Red    |
| CLIC1        | 0  | 0  | CLIC1         | Green  |
| CLIC1        | 1  | 0  | INIT          | Green  |
| CLIC1        | X  | 1  | S2            | Green  |
| CLIC2        | 0  | 0  | CLIC2         | Off    |
| CLIC2        | 1  | X  | CLIC1         | Off    |
| CLIC2        | 0  | 1  | INIT          | Off    |
+--------------+----+----+---------------+--------+

**/


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

static const uint8_t RED = 0x02;
static const uint8_t GREEN = 0x01;
static const uint8_t OFF = 0x00;

enum class State {
    INIT,
    CLIC1, 
    CLIC2
    };

bool debounce(uint8_t mask);
void changeState(State& machine, State nextStateD2, State nextStateD3);
void setColor(uint8_t color);

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    State machine = State::INIT;

    while (true)
    {
        switch (machine)
        {
            case State::INIT:
                setColor(RED);
                changeState(machine, State::CLIC1, State::CLIC1);
                break;

            case State::CLIC1:
                setColor(GREEN);
                changeState(machine, State::INIT, State::CLIC2);
                break;

            case State::CLIC2:
                setColor(OFF);
                changeState(machine, State::CLIC1, State::INIT);
                break;
        }

    }
}

void setColor(uint8_t color)
{
    PORTA = color;
}

bool debounce(uint8_t mask) 
{
    if (PIND & mask)
    {   
        int waitDelay = 10;
        _delay_ms(waitDelay);
        return (PIND & mask);
    }
    return false;
}

void changeState(State& machine, State nextStateD2, State nextStateD3)
{
    const uint8_t MASK_D2 = 0x04;
    const uint8_t MASK_D3 = 0x08;

    while (PIND & MASK_D2 || PIND & MASK_D3)
    {
        if (debounce(MASK_D2))
        {
            machine = nextStateD2;
        }
        else if (debounce(MASK_D3))
        {
            machine = nextStateD3;
        }
    }

}