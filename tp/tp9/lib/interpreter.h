#include <avr/io.h>
#include <counter.h>
#include <led.h>
#include <MotorsController.h>
#include <util/delay.h>
#include <usart.h>
#include <stdio.h>
#include <memoire_24.h>

class Interpreter
{
    Interpreter();
    void interpreter(uint8_t instruction, uint8_t operand);
    void interpretCode(uint16_t startAdress);

private:
    uint8_t  read8Bits();
    uint16_t getNumberInstructions();


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
    
    uint16_t numberInstructions;
    uint16_t currentAdress_;
    uint16_t loopAddress_;
    uint8_t  counter_ = 0;
};