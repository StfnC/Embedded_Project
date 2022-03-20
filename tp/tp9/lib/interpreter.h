#pragma once

#include <avr/io.h>
#include <counter.h>
#include <led.h>
// #include <Notes.h>
#include <MotorsController.h>
#include <util/delay.h>
#include <usart.h>
#include <stdio.h>
#include <memoire_24.h>
#include <debug.h>
#include "operations.h"

class Interpreter {
public:
    Interpreter();
    void interpreter(uint8_t instruction, uint8_t operand);
    uint16_t getNumberInstructions();

private:
    uint8_t read8Bits();

    void dbt();
    void att(uint8_t operand);
    void dal(uint8_t operand);
    void det(uint8_t operand);
    void sgo(uint8_t operand);
    void sar();
    void mar();
    void mav(uint8_t operand);
    void mre(uint8_t operand);
    void trd();
    void trg();
    void dbc(uint8_t operand);
    void fbc();
    void fin();

    bool execute_ = false;

    usart transmitter_;
    MotorsController motorsController_;
    Memoire24CXXX memoire_;
    // Notes song_;
    
    uint16_t rotationTime_ = 500;
    uint16_t numberInstructions = 0;
    uint16_t currentAdress_ = 0;
    uint16_t loopAddress_ = 0;
    uint8_t counter_ = 0;
};
