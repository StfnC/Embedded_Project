#include "interpreter.h"

Interpreter::Interpreter() : transmitter_(),
                             motorsController_(),
                             memoire_() {}

uint8_t Interpreter::read8Bits() {
    uint8_t *numberPtr;
    memoire_.lecture(currentAdress_, numberPtr);
    currentAdress_ += sizeof(uint8_t);
    return *numberPtr;
}

uint16_t Interpreter::getNumberInstructions() {
    uint8_t firstNumberHalf = read8Bits();
    uint16_t numberInstructions;
    numberInstructions = static_cast<uint16_t>(firstNumberHalf) << 8;
    _delay_ms(5);
    uint8_t secondNumberHalf = read8Bits();
    numberInstructions |= static_cast<uint16_t>(secondNumberHalf);
    return numberInstructions - 1;
}

void Interpreter::interpretCode() {
    uint16_t numberInstructions = getNumberInstructions();
    for (uint16_t i = 0; i < numberInstructions; i++)
    {
        uint8_t instruction = read8Bits();
        uint8_t operand = read8Bits();
        interpreter(instruction, operand);
    }
}

void Interpreter::interpreter(uint8_t instruction, uint8_t operand) {
    if (execute_ || instruction == Operations::dbt)
    {
        switch (instruction)
        {
        case Operations::dbt:
            dbt();
            break;

        case Operations::att:
            att(operand);
            break;

        case Operations::dal:
            dal(operand);
            break;

        case Operations::det:
            det(operand);
            break;

        case Operations::sgo:
            sgo(operand);
            break;

        case Operations::sar:
            sar(operand);
            break;

        case Operations::mar1:
        case Operations::mar2:
            mar();
            break;

        case Operations::mav:
            mav(operand);
            break;

        case Operations::mre:
            mre(operand);
            break;

        case Operations::trd:
            trd();
            break;

        case Operations::trg:
            trg();
            break;

        case Operations::dbc:
            dbc(operand);
            break;

        case Operations::fbc:
            fbc();
            break;

        case Operations::fin:
            fin();
            break;
        }
    }
}

void Interpreter::dbt() {
    transmitter_.transmit(0x01);
    execute_ = true;
}

void Interpreter::att(uint8_t operand) {
    transmitter_.transmit(0x02);

    for (uint8_t i = 0; i < operand; i++)
    {
        _delay_ms(25);
    }
}

void Interpreter::dal(uint8_t operand) {
    transmitter_.transmit(0x44);
};

void Interpreter::det(uint8_t operand) {
    transmitter_.transmit(0x45);
}

void Interpreter::sgo(uint8_t operand) {
    transmitter_.transmit(0x48);
}

void Interpreter::sar(uint8_t operand) {
    transmitter_.transmit(0x09);
}

void Interpreter::mar() {
    transmitter_.transmit(0x61);
    motorsController_.setLeftPercentage(0);
    motorsController_.setRightPercentage(0);
}

void Interpreter::mav(uint8_t operand) {
    transmitter_.transmit(0x62);

    uint8_t percentage = operand / 255 * 100;
    motorsController_.setLeftPercentage(percentage);
    motorsController_.setRightPercentage(percentage);
    _delay_ms(5);
}

void Interpreter::mre(uint8_t operand) {
    transmitter_.transmit(0x63);

    uint8_t percentage = operand / 255 * 100;
    motorsController_.changeLeftDirection();
    motorsController_.changeRightDirection();
    motorsController_.setLeftPercentage(percentage);
    motorsController_.setRightPercentage(percentage);
}

void Interpreter::trd() {
    transmitter_.transmit(0x64);
}

void Interpreter::trg() {
    transmitter_.transmit(0x65);
}

void Interpreter::dbc(uint8_t operand) {
    transmitter_.transmit(0xC0);

    loopAddress_ = currentAdress_;
    counter_ = operand;
}

void Interpreter::fbc() {
    transmitter_.transmit(0xC1);

    if (counter_ != 0)
    {
        currentAdress_ = loopAddress_;
    }
}

void Interpreter::fin() {
    transmitter_.transmit(0xFF);
    execute_ = false;
}
