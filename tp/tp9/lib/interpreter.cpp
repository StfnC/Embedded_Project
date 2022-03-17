#include "interpreter.h"

Interpreter::Interpreter() : transmitter_(),
                             motorsController_(),
                             memoire_() {}

uint8_t Interpreter::read8Bits()
{
    uint8_t* numberPtr;
    memoire_.lecture(currentAdress_, numberPtr);
    currentAdress_ += 8;
    return *numberPtr;
}

uint16_t Interpreter::read16Bits()
{
    
}
uint16_t Interpreter::getNumberInstructions()
{
    uint8_t firstNumberHalf = read8Bits();
    uint16_t numberInstructions;     
    numberInstructions = static_cast<uint16_t>(firstNumberHalf) << 8;

    uint8_t secondNumberHalf = read8Bits();
    numberInstructions |= static_cast<uint16_t>(secondNumberHalf);
}

void Interpreter::interpretCode(uint16_t address)
{
    address = currentAdress_;
    uint16_t numberInstructions = getNumberInstructions();

    for (uint16_t i = 0; i < numberInstructions; i++)
    {
        uint8_t instruction = read8Bits();
        uint8_t operand = read8Bits();
        interpreter(instruction, operand);
    }
}

void Interpreter::interpreter(uint8_t instruction, uint8_t operand)
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

        default:
            fin();
            break;
        }
}   

void Interpreter::dbt()
{
    execute_ = true;
    transmitter_ = usart();
    motorsController_ = MotorsController();
}

void Interpreter::att(uint8_t operand)
{
    if (execute_)
    {
        for (uint8_t i = 0; i < operand; i++)
        {
            _delay_ms(25);
        }
    }
}

void Interpreter::dal(uint8_t operand)
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction DAL est executée");
        transmitter_.transmitTextMessage(message, n);
    }
};

void Interpreter::det(uint8_t operand)
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction DET est executée");
        transmitter_.transmitTextMessage(message, n);
    }
}

void Interpreter::sgo(uint8_t operand)
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction SGO est executée");
        transmitter_.transmitTextMessage(message, n);
    }
}

void Interpreter::sar(uint8_t operand)
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction SAR est executée");
        transmitter_.transmitTextMessage(message, n);
    }
}

void Interpreter::mar()
{
    if (execute_)
    {
        motorsController_.setLeftPercentage(0);
        motorsController_.setRightPercentage(0);
    }
}

void Interpreter::mav(uint8_t operand)
{
    if (execute_)
    {
        uint8_t percentage = operand / 255 * 100;
        motorsController_.setLeftPercentage(percentage);
        motorsController_.setRightPercentage(percentage);
    }
}

void Interpreter::mre(uint8_t operand)
{
    if (execute_)
    {
        uint8_t percentage = operand / 255 * 100;
        motorsController_.changeLeftDirection();
        motorsController_.changeRightDirection();
        motorsController_.setLeftPercentage(percentage);
        motorsController_.setRightPercentage(percentage);
    }
}

void Interpreter::trd()
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction TRD est executée");
        transmitter_.transmitTextMessage(message, n);
    }
}

void Interpreter::trg()
{
    if (execute_)
    {
        char message[31];
        int n;
        n = sprintf(message, "L'instruction TRG est executée");
        transmitter_.transmitTextMessage(message, n);
    }
}

void Interpreter::dbc(uint8_t operand)
{
    if (execute_)
    {
        loopAddress_ = currentAdress_;
        counter_ = operand;
    }
}

void Interpreter::fbc()
{
    if (execute_)
    {
        if (counter_ != 0)
        {
            currentAdress_ = loopAddress_;
        }
    }
}

void Interpreter::fin()
{
    if (execute_)
    {
        execute_ = false;
    }
}
