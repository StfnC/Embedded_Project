#pragma once
#include <MotorsController.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <memoire_24.h>

enum class RerunManagerState {
    INERT,
    MEMORIZING,
    RERUN
};

class RerunManager {
    public:
        static void manageRerun();
        static void setRerunManagerState(RerunManagerState state);
        static void stopRerunManagement();
        static void initializationRead();
        static void initialization();
        static void stopRegister();
        static void stopRerun();

    private:
        static const uint8_t TIMER_DURATION = 0xFF;
        static uint16_t address_;
        static Memoire24CXXX memory_;
        static RerunManagerState state_;

        static void readMemory();
        static void writeMemory();
};