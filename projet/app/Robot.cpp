#include "Robot.h"

State Robot::currentState_ = State::INIT;

void Robot::init() {
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
}

void Robot::manageStateStartRerun() {
}

void Robot::manageStateRerun() {
}

void Robot::manageStateEndRerun() {
}

void Robot::manageStateStartAutonomous() {
}

void Robot::manageStateStartMemorizing() {
}

void Robot::manageStateFollowWall() {
}

void Robot::manageStateFollowLight() {
}

void Robot::manageStateStopMemorizing() {
}

void Robot::manageStateStartUTurn() {
}

void Robot::manageStateUTurn() {
}

void Robot::manageStateEndAutonomous() {
}
