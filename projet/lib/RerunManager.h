#pragma once
#include <MotorsController.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <memoire_24.h>
#include <usart.h>

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
        static void initialization();
        static void stopRegister();
        static void stopRerun();
        static RerunManagerState getState() { return state_;}

    private:
        static void stopWheels();
        static void stopRerunManagement();
        static void readMemory();
        static void writeMemory();

        static const uint8_t TIMER_DURATION = 50;
        static uint16_t address_;
        static Memoire24CXXX memory_;
        static RerunManagerState state_;
};