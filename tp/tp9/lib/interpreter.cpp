#include "interpreter.h"

Interpreter::Interpreter() : transmitter_(),
                             motorsController_(),
                             memoire_() {}

uint8_t Interpreter::read8Bits()
{
    uint8_t *numberPtr;
    memoire_.lecture(currentAdress_, numberPtr);
    currentAdress_ += sizeof(uint8_t);
    return *numberPtr;
}

uint16_t Interpreter::getNumberInstructions()
{
    uint8_t firstNumberHalf = read8Bits();
    uint16_t numberInstructions;
    numberInstructions = static_cast<uint16_t>(firstNumberHalf) << 8;
    _delay_ms(5);
    uint8_t secondNumberHalf = read8Bits();
    numberInstructions |= static_cast<uint16_t>(secondNumberHalf);
    return numberInstructions - 1;
}

void Interpreter::interpretCode()
{
    uint16_t numberInstructions = getNumberInstructions();
    _delay_ms(5);
    // transmitter_.transmit(numberInstructions);
    for (uint16_t i = 0; i < numberInstructions; i++)
    {
        uint8_t instruction = read8Bits();
        uint8_t operand = read8Bits();
        interpreter(instruction, operand);
    }
}

void Interpreter::interpreter(uint8_t instruction, uint8_t operand)
{
    if (execute_ || instruction == 0x01)
    {
        switch (instruction)
        {
        case 0x01:
            dbt();
            break;

        case 0x02:
            att(operand);
            break;

        case 0x44:
            dal(operand);
            break;

        case 0x45:
            det(operand);
            break;

        case 0x48:
            sgo(operand);
            break;

        case 0x09:
            sar(operand);
            break;

        case 0x60:
        case 0x61:
            mar();
            break;

        case 0x62:
            mav(operand);
            break;

        case 0x63:
            mre(operand);
            break;

        case 0x64:
            trd();
            break;

        case 0x65:
            trg();
            break;

        case 0xC0:
            dbc(operand);
            break;

        case 0xC1:
            fbc();
            break;

        case 0xFF:
            fin();
            break;
        }
    }
}

void Interpreter::dbt()
{
    transmitter_.transmit(0x01);
    execute_ = true;
}

void Interpreter::att(uint8_t operand)
{
    transmitter_.transmit(0x02);

    for (uint8_t i = 0; i < operand; i++)
    {
        _delay_ms(25);
    }
}

void Interpreter::dal(uint8_t operand)
{
    transmitter_.transmit(0x44);
};

void Interpreter::det(uint8_t operand)
{
    transmitter_.transmit(0x45);
}

void Interpreter::sgo(uint8_t operand)
{
    transmitter_.transmit(0x48);
}

void Interpreter::sar(uint8_t operand)
{
    transmitter_.transmit(0x09);
}

void Interpreter::mar()
{
    transmitter_.transmit(0x61);
    motorsController_.setLeftPercentage(0);
    motorsController_.setRightPercentage(0);
}

void Interpreter::mav(uint8_t operand)
{
    transmitter_.transmit(0x62);

    uint8_t percentage = operand / 255 * 100;
    motorsController_.setLeftPercentage(percentage);
    motorsController_.setRightPercentage(percentage);
    _delay_ms(5);
}

void Interpreter::mre(uint8_t operand)
{
    transmitter_.transmit(0x63);

    uint8_t percentage = operand / 255 * 100;
    motorsController_.changeLeftDirection();
    motorsController_.changeRightDirection();
    motorsController_.setLeftPercentage(percentage);
    motorsController_.setRightPercentage(percentage);
}

void Interpreter::trd()
{
    transmitter_.transmit(0x64);
}

void Interpreter::trg()
{
    transmitter_.transmit(0x65);
}

void Interpreter::dbc(uint8_t operand)
{
    transmitter_.transmit(0xC0);

    loopAddress_ = currentAdress_;
    counter_ = operand;
}

void Interpreter::fbc()
{
    transmitter_.transmit(0xC1);

    if (counter_ != 0)
    {
        currentAdress_ = loopAddress_;
    }
}

void Interpreter::fin()
{
    transmitter_.transmit(0xFF);
    // execute_ = false;
}
