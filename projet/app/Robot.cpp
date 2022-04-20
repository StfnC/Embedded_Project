#define F_CPU 8000000L

#include "Robot.h"

State Robot::currentState_ = State::INIT;
led Robot::led_(DDA0, DDA1);

void Robot::init() {
    SystemTimer::init();
    SystemTimer::start();
    RerunManager::initialization();
    MotorsController::initialization();
    DistanceSensor::initialization();
    LightController::initialization();
    ButtonPressDetector::init();
    BuzzerController::initBuzzer();
}

void Robot::run() {
    manageStateMachine();
    RerunManager::manageRerun();
    ConcurrentMusicPlayer::playMusic();
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
    
    if (ButtonPressDetector::isSmallButtonPressed()) {
        currentState_ = State::START_AUTONOMOUS;
    } else if (ButtonPressDetector::isBreadButtonPressed()) {
        currentState_ = State::START_RERUN;
    }
}

void Robot::manageStateStartRerun() {
    DEBUG_PRINT_MESSAGE("Current State : START_RERUN\n");
    for (uint8_t i = 0; i < NB_ITER_FOR_THREE_SECONDS_AT_FIVE_HZ; i++) {
        led_.setRed();
        _delay_ms(BLINKING_DELAY_FOR_FIVE_HERZTZ);
        led_.setOff();
        _delay_ms(BLINKING_DELAY_FOR_FIVE_HERZTZ);
    }

    RerunManager::initializationRead();

    ConcurrentMusicPlayer::init(MusicTrack::SECOND_TRACK);
    ConcurrentMusicPlayer::setTrackPlayingStatus(true);
    
    led_.setOff();
    
    currentState_ = State::RERUN;
}

void Robot::manageStateRerun() {
    DEBUG_PRINT_MESSAGE("Current State : RERUN\n");
    if (RerunManager::getState() == RerunManagerState::END_MEMORY) {
        currentState_ = State::END_RERUN;
    }
}

void Robot::manageStateEndRerun() {
    DEBUG_PRINT_MESSAGE("Current State : END_RERUN\n");
    led_.setGreen();
    RerunManager::stopRerun();
    ConcurrentMusicPlayer::setTrackPlayingStatus(false);
}

void Robot::manageStateStartAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : START_AUTONOMOUS\n");
    for (uint8_t i = 0; i < NB_ITER_FOR_THREE_SECONDS_AT_FIVE_HZ; i++) {
        led_.setGreen();
        _delay_ms(BLINKING_DELAY_FOR_FIVE_HERZTZ);
        led_.setOff();
        _delay_ms(BLINKING_DELAY_FOR_FIVE_HERZTZ);
    }

    led_.setOff();

    ConcurrentMusicPlayer::init(MusicTrack::FIRST_TRACK);
    ConcurrentMusicPlayer::setTrackPlayingStatus(true);

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
    if (ButtonPressDetector::isSmallButtonPressed()) {
        currentState_ = State::END_AUTONOMOUS;
        return;
    }
    
    if (ButtonPressDetector::isBreadButtonPressed()) {
        currentState_ = State::STOP_MEMORIZING;
        return;
    }    

    LightController::followLight();

    uint8_t distance = DistanceSensor::getDistanceCm();

    DEBUG_PRINT_MESSAGE_WITH_VALUE("Distance : %d\n", distance);

    if (distance < LOW_WALL_DETECTION_LIMIT) {
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
    _delay_ms(ONE_SECOND_DELAY);
    currentState_ = State::U_TURN;
}

void Robot::manageStateUTurn() {
    DEBUG_PRINT_MESSAGE("Current State : U_TURN\n");
    led_.setAmber();
    MotorsController::changeLeftDirection(Direction::Forward);
    MotorsController::changeRightDirection(Direction::Forward);
    MotorsController::setLeftPercentage(UTURN_LEFT_SPEED);
    MotorsController::setRightPercentage(UTURN_LEFT_SPEED);
    _delay_ms(FORWARD_DELAY_UTURN);
    MotorsController::setRightPercentage(UTURN_RIGHT_SPEED);
    _delay_ms(UTURN_TURNING_DELAY);
    while (DistanceSensor::getDistanceCm() > HIGH_WALL_DETECTION_LIMIT);
    
    led_.setOff();;

    currentState_ = State::FOLLOW_WALL;
}

void Robot::manageStateEndAutonomous() {
    DEBUG_PRINT_MESSAGE("Current State : END_AUTONOMOUS\n");
    if (RerunManager::getState() != RerunManagerState::END_MEMORY) {
        led_.setRed();
        RerunManager::stopRegister();
    }

    ConcurrentMusicPlayer::setTrackPlayingStatus(false);

    led_.setGreen();
}
