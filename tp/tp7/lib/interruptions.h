/*
 * Librairie permettant le contrôle de certaines configurations d'interruptions 

 * du microcontroleur ATMega16 de Atmel.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Code qui n'est sous aucune license.
 *
 */

#include <avr/interrupt.h>

enum class InterruptMode
{
    LowLevelInterrupt,
    AnyEdgeInterrupt,
    FallingEdgeInterrupt,
    RisingEdgeInterrupt

};

class buttonInterrupt
{
public:

    
    buttonInterrupt(uint8_t interruptNumber, InterruptMode mode);
    ~buttonInterrupt();
    

private:
    uint8_t eicraValue_;
    uint8_t eimskValue_;
};
