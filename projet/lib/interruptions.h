/**
 * Definition of the ButtonInterrupt class and the associated enum
 * 
 * \file interruptions.h
 * \author Faneva Rakotoarivony
 * \date March 13 2022
 *
 */
#pragma once
#include <avr/interrupt.h>

enum class InterruptMode {
    LowLevelInterrupt,
    AnyEdgeInterrupt,
    FallingEdgeInterrupt,
    RisingEdgeInterrupt
};

class ButtonInterrupt {
   public:
    ButtonInterrupt(uint8_t interruptNumber, InterruptMode mode);
    ~ButtonInterrupt() {}

   private:
    static constexpr uint8_t INTERRUPT_NUMBER_MULTIPLIER = 2;

    uint8_t eicraValue_;
    uint8_t eimskValue_;
};
