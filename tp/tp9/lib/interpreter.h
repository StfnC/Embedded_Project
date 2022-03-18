#pragma once

#include <avr/io.h>
#include <counter.h>
#include <led.h>
#include <MotorsController.h>
#include <util/delay.h>
#include <usart.h>
#include <stdio.h>
#include <memoire_24.h>
#include <debug.h>

enum class Operations
{
    dbt = 0x01,
    att = 0x02,
    dal = 0x44,
    det = 0x45,
    sgo = 0x48,
    sar = 0x09,
    mar1 = 0x60,
    mar2 = 0x61,
    mav = 0x62,
    mre = 0x63, 
    trd = 0x64,
    dbc = 0xC0, 
    fbc = 0xC1,
    fin = 0xFF
};


class Interpreter
{
public:
    Interpreter();
    void interpreter(uint8_t instruction, uint8_t operand);
    void interpretCode();
    uint16_t getNumberInstructions();

private:
    uint8_t  read8Bits();

    void dbt();
    void att(uint8_t operand);
    void dal(uint8_t operand);
    void det(uint8_t operand);
    void sgo(uint8_t operand);
    void sar(uint8_t operand);
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
    
    uint16_t numberInstructions = 0;
    uint16_t currentAdress_ = 0;
    uint16_t loopAddress_ = 0;
    uint8_t  counter_ = 0;
};