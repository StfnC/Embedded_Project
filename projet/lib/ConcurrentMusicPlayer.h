#pragma once

#include <avr/io.h>

#include "BuzzerController.h"
#include "memoire_24.h"
#include "operations.h"
#include "SystemTimer.h"
#include "musicPlayerConstants.h"

enum class MusicTrack {
    FIRST_TRACK,
    SECOND_TRACK
};

class ConcurrentMusicPlayer {
    public:
        static void init(MusicTrack track);
        static void setTrackPlayingStatus(bool trackPlaying);
        static void playMusic();
        
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
        static bool canPlay();

        static const uint32_t DELAY_MS = 25;

        static Memoire24CXXX memory_;

        static uint16_t loopInstructionNumber_;
        static uint16_t numberInstructions_;
        static uint16_t currentAdress_;
        static uint16_t loopAddress_;
        static uint8_t counter_;
        static uint32_t afterWaitTime_;
        static bool startTrack_;
};
