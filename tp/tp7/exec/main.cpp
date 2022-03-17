/**
Program implementing a finite state machine following the following diagram.
 \file   pb1.cpp
 \author Rakotoarivony Faneva #2131367 and Lina Belloui #...
 \date   january 30 2022
Created janvier 17 2022

PIN A OUT (A0 et A1 : DEL)
PIN D IN  (D2 et D3 : BUTTONS)


+--------------+----+----+---------------+--------+
| State        | D2 | D3 | Next State    | Sortie |
+--------------+----+----+---------------+--------+
| INIT         | 0  |  0 | INIT          | Off    |
| INIT         | X  |  1 | INIT          | Off    |
| INIT         | 1  |  0 | CLIC1         | Off    |
| CLIC1        | 0  |  0 | CLIC1         | Off    |
| CLIC1        | 1  |  0 | CLIC2         | Off    |
| CLIC1        | X  |  1 | INIT          | Off    |
| CLIC2        | 0  |  0 | CLIC2         | Off    |
| CLIC2        | 1  |  0 | CLIC3         | Off    |
| CLIC2        | X  |  1 | INIT          | Off    |
| CLIC3        | 0  |  0 | CLIC3         | RED    |
| CLIC3        | 1  |  0 | INIT          | RED    |
| CLIC3        | X  |  1 | INIT          | RED    |
+--------------+----+----+---------------+--------+


**/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <debug.h>

static const uint8_t OFF = 0x00;
static const uint8_t RED = 0x02;

static const uint8_t MASK_D2 = 0x04;
static const uint8_t MASK_D3 = 0x08;

enum class State {
    INIT,   
    CLIC1, 
    CLIC2, 
    CLIC3  
};

bool debounce(uint8_t mask);
void changeState(State& machine, State nextStateD2, State nextStateD3);
void setColor(uint8_t color);

int main()
{
    DDRA = 0xff;
    DDRD = 0x00;

    uint8_t msg[] = "Hello Debug!";
    uint8_t msgLength = 13;
    
    // DEBUG_PRINT_MESSAGE(msg, msgLength);

    State machine = State::INIT;

    
    while (true)
    {
        DEBUG_PRINT_VARIABLE(machine);

        switch(machine)
        {

            case State::INIT:
                setColor(OFF);
                changeState(machine, State::CLIC1, State::INIT);
                break;

            case State::CLIC1:
                setColor(OFF);
                changeState(machine, State::CLIC2, State::INIT);
                break;

            case State::CLIC2:
                setColor(OFF);
                changeState(machine, State::CLIC3, State::INIT);
                break;

            case State::CLIC3:
                setColor(OFF);
                changeState(machine, State::INIT, State::INIT);
                break;
        }

    }
}

bool debounce(uint8_t mask) 
{
    if (PIND & mask)
    {   
        // DEBUG_COMPARE_SIGNAL(PIND, PIND2, 1);
        const int WAIT_DELAY = 10;
        _delay_ms(WAIT_DELAY);
        return (PIND & mask);
    }
    return false;
}

void changeState(State& machine, State nextStateD2, State nextStateD3)
{
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

void setColor(uint8_t color)
{
    PORTA = color;
}