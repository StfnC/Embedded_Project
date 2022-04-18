#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <MotorsController.h>
#include "usart.h"

enum class State {
    INERT, 
    MEMORIZING,
    RERUN
};

class MemoryManager {
public:
    static void manageRun();
    static void initializationRead();
    static void initialization();
    static void setIntervalle(uint16_t duration);
    static State state_;
    static void readMemory();
    static void writeMemory();
private:
    static uint16_t address_;
    static Memoire24CXXX memory;
};