/**
 * 
 * Define the Robot state enum
 * 
 * \file State.h
 * \author Lina Belloui, Stefan Cotargasanu, Faneva Rakotoarivony and Justine Sauquet
 * \date April 20th 2022
 * 
 */

enum class State {
    INIT,
    START_RERUN,
    RERUN,
    END_RERUN,
    START_AUTONOMOUS,
    START_MEMORIZING,
    FOLLOW_WALL,
    FOLLOW_LIGHT,
    STOP_MEMORIZING,
    START_U_TURN,
    U_TURN,
    END_AUTONOMOUS
};