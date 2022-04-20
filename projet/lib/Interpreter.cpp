/**
 * Implementation of the Interpreter methods
 *
 * \file Interpreter.cpp
 * \author Stefan Cotargasanu Faneva Rakotoarivony Lina Belloui Justine Sauquet
 * \date March 22 2022
 *
 */
#include "Interpreter.h"

Interpreter::Interpreter() : memoire_() {
}

uint8_t Interpreter::read8Bits() {
    uint8_t* numberPtr = nullptr;
    memoire_.lecture(currentAdress_, numberPtr);
    currentAdress_++;
    return *numberPtr;
}

void Interpreter::interpretCode() {
    readNumberInstructions();

    for (; numberInstructions_ > 0; numberInstructions_--) {
        interpretLine();
    }
}

void Interpreter::interpretLine() {
    uint8_t operation = read8Bits();
    uint8_t operand = read8Bits();
    interpreter(operation, operand);
}

void Interpreter::readNumberInstructions() {
    uint8_t firstNumberHalf = read8Bits();
    numberInstructions_ = static_cast<uint16_t>(firstNumberHalf) << BIT_SHIFT_FOR_UINT8_CONVERSION;
    uint8_t secondNumberHalf = read8Bits();
    numberInstructions_ |= static_cast<uint16_t>(secondNumberHalf);
    numberInstructions_ -= N_BYTES_FOR_PROGRAM_SIZE;
    numberInstructions_ /= N_BYTES_FOR_PROGRAM_SIZE;
}

void Interpreter::interpreter(uint8_t instruction, uint8_t operand) {
    if (execute_ || instruction == Operations::dbt) {
        switch (instruction) {
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
                sar();
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
    execute_ = true;
}

void Interpreter::att(uint8_t operand) {
    for (uint8_t i = 0; i < operand; i++) {
        _delay_ms(TWENTY_FIVE_SECOND_DELAY);
    }
}

void Interpreter::dal(uint8_t operand) {  // allumer la del
    led led0(DDA0, DDA1);
    led0.setGreen();
};

void Interpreter::det(uint8_t operand) {  // eteindre del
    led led0(DDA0, DDA1);
    led0.setOff();
}

void Interpreter::sgo(uint8_t operand) {  // jouer une sonorité
    BuzzerController::playNote(operand);
}

void Interpreter::sar() {  // arrêter de jouer la sonorité
    BuzzerController::stopNote();
}

void Interpreter::mar() {  // arrête les deux moteurs
    MotorsController::setRightPercentage(0);
    MotorsController::setLeftPercentage(0);
}

void Interpreter::mav(uint8_t operand) {  // avancer
    uint8_t percentage = (operand / UINT8_MAX) * HUNDRED_PERCENT;
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(percentage);
    MotorsController::setRightPercentage(percentage);
    _delay_ms(TWENTY_SECOND_DELAY);
}

void Interpreter::mre(uint8_t operand) {  // reculer
    uint8_t percentage = operand / UINT8_MAX * HUNDRED_PERCENT;
    MotorsController::changeLeftDirection(Direction::Reverse);
    MotorsController::changeRightDirection(Direction::Reverse);
    MotorsController::setLeftPercentage(percentage);
    MotorsController::setRightPercentage(percentage);
}

void Interpreter::trd() {  // tourner à droite
    uint8_t rightPercent = MotorsController::getRightPercentage();
    uint8_t leftPercent = MotorsController::getLeftPercentage();

    MotorsController::setRightPercentage(HUNDRED_PERCENT);
    MotorsController::invertRightDirection();

    MotorsController::setLeftPercentage(HUNDRED_PERCENT);

    _delay_ms(ROTATION_TIME);  // duree de rotation

    MotorsController::invertRightDirection();
    MotorsController::setRightPercentage(rightPercent);
    MotorsController::setLeftPercentage(leftPercent);
}

void Interpreter::trg() {  // tourner à gauche
    uint8_t rightPercent = MotorsController::getRightPercentage();
    uint8_t leftPercent = MotorsController::getLeftPercentage();

    MotorsController::setRightPercentage(HUNDRED_PERCENT);

    MotorsController::setLeftPercentage(HUNDRED_PERCENT);
    MotorsController::invertLeftDirection();

    _delay_ms(ROTATION_TIME);  // duree de rotation

    MotorsController::setRightPercentage(rightPercent);
    MotorsController::invertLeftDirection();
    MotorsController::setLeftPercentage(leftPercent);
}

void Interpreter::dbc(uint8_t operand) {  // début de boucle
    loopAddress_ = currentAdress_;
    loopInstructionNumber_ = numberInstructions_;
    counter_ = operand + 1;
}

void Interpreter::fbc() {  // fin de boucle
    if (counter_ != 0) {
        currentAdress_ = loopAddress_;
        counter_--;
        numberInstructions_ = loopInstructionNumber_;
    }
}

void Interpreter::fin() {
    execute_ = false;
}
