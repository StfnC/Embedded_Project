#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <MotorsController.h>
#include "usart.h"

class RerunManager {
public:
    static void initializationRead();
    static void initialization();
    static void setIntervalle(uint16_t duration);
    static void writeMemory();
    static void readMemory();
private:
    static uint16_t address_;
    static Memoire24CXXX memory_;
};