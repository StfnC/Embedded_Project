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
        static void setIntervalle(uint16_t duration);
        static void writeMemory();
        static void readMemory();

    private:
        static uint16_t address_;
        static Memoire24CXXX memory_;
        static RerunManagerState state_;
};