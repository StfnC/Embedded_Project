#pragma once

#include <MotorsController.h>
#include <avr/io.h>
#include <memoire_24.h>
#include <SystemTimer.h>

enum class RerunManagerState {
    INERT,
    MEMORIZING,
    RERUN,
    END_MEMORY
};

class RerunManager {
    public:
        static void manageRerun();
        static void setRerunManagerState(RerunManagerState state);
        static void initializationRead();
        static void stopRegister();
        static void stopRerun();
        static RerunManagerState getState() { return state_;}

    private:
        static void readMemory();
        static void writeMemory();

        static constexpr uint8_t VALUE_FOR_SHIFT_EIGHTH_BIT = 7;
        static constexpr uint8_t SEVEN_FIRST_BITS_MASK = 0x7F;
        static constexpr uint8_t MEMORY_ACCESS_INTERVAL = 50;
        static constexpr uint8_t END_OF_RERUN_MARKER = 0xFF;
        static uint16_t address_;
        static Memoire24CXXX memory_;
        static RerunManagerState state_;
        static uint32_t lastMemoryAccess_;
};