#define F_CPU 8000000L

#include "Robot.h"

#include <debug.h>
#include <util/delay.h>

#include <MotorsController.h>
#include <DistanceSensor.h>
#include <WallFollower.h>

State Robot::currentState_ = State::INIT;
led Robot::led_(DDA0, DDA1);

void Robot::init() {
    MotorsController::initialization();
    DistanceSensor::initialization();
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
            manageStateStartMemorizing();
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
    // FIXME: ONLY FOR TESTING
    _delay_ms(4000);
    currentState_ = State::START_AUTONOMOUS;
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

    led_.setOff();
    currentState_ = State::RERUN;
}

void Robot::manageStateRerun() {
    DEBUG_PRINT_MESSAGE("Current State : RERUN\n");
}

void Robot::manageStateEndRerun() {
    DEBUG_PRINT_MESSAGE("Current State : END_RERUN\n");
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
    currentState_ = State::FOLLOW_WALL;
}

void Robot::manageStateFollowWall() {
    DEBUG_PRINT_MESSAGE("Current State : FOLLOW_WALL\n");
    // FIXME: WallFollower needs a way to tell us that it doesn't detect a wall
    WallFollower::followWall();
}

void Robot::manageStateFollowLight() {
    DEBUG_PRINT_MESSAGE("Current State : FOLLOW_LIGHT\n");
}

void Robot::manageStateStopMemorizing() {
    DEBUG_PRINT_MESSAGE("Current State : STOP_MEMORIZING\n");
}

void Robot::manageStateStartUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : START_U_TURN\n");
}

void Robot::manageStateUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : U_TURN\n");
}

void Robot::manageStateEndAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : END_AUTONOMOUS\n");
}
