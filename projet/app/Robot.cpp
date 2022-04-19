#define F_CPU 8000000L

#include "Robot.h"

#include <debug.h>
#include <util/delay.h>

#include <MotorsController.h>
#include <DistanceSensor.h>
#include <WallFollower.h>
#include <LightController.h>
#include <ButtonPressDetector.h>
#include <RerunManager.h>

State Robot::currentState_ = State::INIT;
led Robot::led_(DDA0, DDA1);

ISR(TIMER2_COMPA_vect) {
    RerunManager::manageRerun();
}

void Robot::init() {
    MotorsController::initialization();
    DistanceSensor::initialization();
    LightController::initialization();
    ButtonPressDetector::init();
}

void Robot::run() {
    manageStateMachine();
}

void Robot::manageStateMachine() {
    switch (currentState_) {
        case State::INIT:
            manageStateInit();
            break;
        case State::START_RERUN:
            manageStateStartRerun();
            break;
        case State::RERUN:
            manageStateRerun();
            break;
        case State::END_RERUN:
            manageStateEndRerun();
            break;
        case State::START_AUTONOMOUS:
            manageStateStartAutonomous();
            break;
        case State::START_MEMORIZING:
            manageStateStartMemorizing();
            break;
        case State::FOLLOW_WALL:
            manageStateFollowWall();
            break;
        case State::FOLLOW_LIGHT:
            manageStateFollowLight();
            break;
        case State::STOP_MEMORIZING:
            manageStateStopMemorizing();
            break;
        case State::START_U_TURN:
            manageStateStartUTurn();
            break;
        case State::U_TURN:
            manageStateUTurn();
            break;
        case State::END_AUTONOMOUS:
            manageStateEndAutonomous();
            break;
    }
}

void Robot::manageStateInit() {
    DEBUG_PRINT_MESSAGE("Current State : INIT\n");
    
    if (ButtonPressDetector::wasSmallButtonPressed()) {
        currentState_ = State::START_AUTONOMOUS;
        ButtonPressDetector::reset();
    } else if (ButtonPressDetector::wasBreadButtonPressed()) {
        currentState_ = State::START_RERUN;
        ButtonPressDetector::reset();
    }
}

void Robot::manageStateStartRerun() {
    DEBUG_PRINT_MESSAGE("Current State : START_RERUN\n");
    // FIXME: -Maybe use a timer instead
    //        -Use constants
    for (uint8_t i = 0; i < 15; i++) {
        led_.setRed();
        _delay_ms(100);
        led_.setOff();
        _delay_ms(100);
    }
    RerunManager::initializationRead();
    led_.setOff();
    currentState_ = State::RERUN;
}

void Robot::manageStateRerun() {
    DEBUG_PRINT_MESSAGE("Current State : RERUN\n");
    // FIXME: BLOCKING
    if (RerunManager::getState() == RerunManagerState::INERT) {
        currentState_ = State::END_RERUN;
    }
}

void Robot::manageStateEndRerun() {
    DEBUG_PRINT_MESSAGE("Current State : END_RERUN\n");
    led_.setGreen();
    MotorsController::setLeftPercentage(0);
    MotorsController::setRightPercentage(0);
    // RerunManager::stopRerun();
}

void Robot::manageStateStartAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : START_AUTONOMOUS\n");
    // FIXME: This can be extracted to a function (same code as Start_Rerun)
    for (uint8_t i = 0; i < 15; i++) {
        led_.setGreen();
        _delay_ms(100);
        led_.setOff();
        _delay_ms(100);
    }

    led_.setOff();
    currentState_ = State::START_MEMORIZING;
}

void Robot::manageStateStartMemorizing() {
    DEBUG_PRINT_MESSAGE("Current State : START_MEMORIZING\n");
    RerunManager::initialization();
    RerunManager::setRerunManagerState(RerunManagerState::MEMORIZING);
    currentState_ = State::FOLLOW_WALL;
}

void Robot::manageStateFollowWall() {
    DEBUG_PRINT_MESSAGE("Current State : FOLLOW_WALL\n");

    WallFollower::followWall();

    if (!WallFollower::isWallDetected()) {
        currentState_ = State::FOLLOW_LIGHT;
    }
}

void Robot::manageStateFollowLight() {
    DEBUG_PRINT_MESSAGE("Current State : FOLLOW_LIGHT\n");
    if (ButtonPressDetector::wasSmallButtonPressed()) {
        currentState_ = State::END_AUTONOMOUS;
        ButtonPressDetector::reset();
        return;
    }
    
    if (ButtonPressDetector::wasBreadButtonPressed()) {
        currentState_ = State::STOP_MEMORIZING;
        ButtonPressDetector::reset();
        return;
    }    

    LightController::followLight();

    uint8_t distance = DistanceSensor::getDistanceCm();

    DEBUG_PRINT_MESSAGE_WITH_VALUE("Distance : %d\n", distance);

    // FIXME:-Create constant for when robot is close to wall (10 cm?)
    if (distance < 15) {
        currentState_ = State::FOLLOW_WALL;
    }   
}

void Robot::manageStateStopMemorizing() {
    DEBUG_PRINT_MESSAGE("Current State : STOP_MEMORIZING\n");
    RerunManager::stopRegister();
    currentState_ = State::START_U_TURN;
}

void Robot::manageStateStartUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : START_U_TURN\n");
    // FIXME: Create constant
    _delay_ms(1000);
    currentState_ = State::U_TURN;
}

void Robot::manageStateUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : U_TURN\n");
    led_.setAmber();
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(80);
    MotorsController::setRightPercentage(80);
    _delay_ms(400);
    MotorsController::setRightPercentage(55);
    _delay_ms(3000);
    // FIXME: Constant
    while (DistanceSensor::getDistanceCm() > 30);
    

    led_.setOff();;

    // FIXME: Maybe should be Follow_Light?
    currentState_ = State::FOLLOW_WALL;
}

void Robot::manageStateEndAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : END_AUTONOMOUS\n");
    // FIXME: Make sure that the robot isn't memorizing anymore
}
