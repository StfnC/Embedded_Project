#pragma once

#include <avr/io.h>
#include <util/delay.h>

#include "BuzzerController.h"
#include "memoire_24.h"
#include "operations.h"
#include "usart.h"

class ConcurrentMusicPlayer {
    public:
        static void interpretCode();
        
    private:
        static uint8_t read8Bits();
        static void readNumberInstructions();
        static void interpretLine();
        static void interpreter(uint8_t instruction, uint8_t operand);

        static void dbt();
        static void att(uint8_t operand);
        static void sgo(uint8_t operand);
        static void sar();
        static void dbc(uint8_t operand);
        static void fbc();
        static void fin();

        static const uint16_t ROTATION_TIME = 515;

        static bool execute_;

        static Memoire24CXXX memory_;

        static uint16_t loopInstructionNumber_;
        static uint16_t numberInstructions_;
        static uint16_t currentAdress_;
        static uint16_t loopAddress_;
        static uint8_t counter_;
};
