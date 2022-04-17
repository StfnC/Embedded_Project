#define F_CPU 8000000L

#include "Robot.h"

#include <debug.h>
#include <util/delay.h>

#include <MotorsController.h>
#include <DistanceSensor.h>
#include <WallFollower.h>
#include <LightController.h>
#include <ButtonPressDetector.h>

State Robot::currentState_ = State::INIT;
led Robot::led_(DDA0, DDA1);

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
    if (distance < 10) {
        currentState_ = State::FOLLOW_WALL;
    }   
}

void Robot::manageStateStopMemorizing() {
    DEBUG_PRINT_MESSAGE("Current State : STOP_MEMORIZING\n");
    currentState_ = State::START_U_TURN;
}

void Robot::manageStateStartUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : START_U_TURN\n");
    currentState_ = State::U_TURN;
}

void Robot::manageStateUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : U_TURN\n");
    // FIXME: Maybe should be Follow_Light?
    currentState_ = State::FOLLOW_WALL;
}

void Robot::manageStateEndAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : END_AUTONOMOUS\n");
    // FIXME: Make sure that the robot isn't memorizing anymore
}
