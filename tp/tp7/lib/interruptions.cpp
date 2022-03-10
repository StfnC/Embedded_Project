#include "interruptions.h"


buttonInterrupt::buttonInterrupt(uint8_t interruptNumber, InterruptMode mode)
{
    EIMSK |= _BV(interruptNumber);
    
    switch (mode)
    {
        case InterruptMode::LowLevelInterrupt:
            EICRA &= ~(_BV(ISC00) << (2 * interruptNumber) | _BV(ISC01) << (2 * interruptNumber)); 
            break;
        
        case InterruptMode::AnyEdgeInterrupt:
            EICRA &= ~(_BV(ISC01) << (2 * interruptNumber));
            EICRA |= (_BV(ISC00) << (2 * interruptNumber));

        case InterruptMode::FallingEdgeInterrupt:
            EICRA &= ~(_BV(ISC00) << (2 * interruptNumber));
            EICRA |= (_BV(ISC01) << (2 * interruptNumber));      

        case InterruptMode::RisingEdgeInterrupt:
            EICRA |= _BV(ISC00) | _BV(ISC01);
}