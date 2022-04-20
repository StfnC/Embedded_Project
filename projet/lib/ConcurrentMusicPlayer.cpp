#include "ConcurrentMusicPlayer.h"

Memoire24CXXX ConcurrentMusicPlayer::memory_;
uint16_t ConcurrentMusicPlayer::loopInstructionNumber_ = 0;
uint16_t ConcurrentMusicPlayer::numberInstructions_ = 0;
uint16_t ConcurrentMusicPlayer::currentAdress_ = music::START_OF_MUSIC_ADDRESS;
uint16_t ConcurrentMusicPlayer::loopAddress_ = 0;
uint8_t ConcurrentMusicPlayer::counter_ = 0;
uint32_t ConcurrentMusicPlayer::afterWaitTime_ = 0;
bool ConcurrentMusicPlayer::startTrack_ = false;

void ConcurrentMusicPlayer::init(MusicTrack track) {
    currentAdress_ = music::START_OF_MUSIC_ADDRESS;
    afterWaitTime_ = SystemTimer::getTimer();
    
    readNumberInstructions();

    switch (track) {
        case MusicTrack::FIRST_TRACK:
            break;
        case MusicTrack::SECOND_TRACK:
            currentAdress_ += 2 * numberInstructions_;
            numberInstructions_ = 0;
            readNumberInstructions();
            break;
    }
}

uint8_t ConcurrentMusicPlayer::read8Bits() {
    uint8_t* numberPtr = nullptr;
    memory_.lecture(currentAdress_, numberPtr);
    currentAdress_++;
    return *numberPtr;
}

void ConcurrentMusicPlayer::playMusic() {
    interpretLine();
}

void ConcurrentMusicPlayer::interpretLine() {
    if (canPlay()) {
        uint8_t operation = read8Bits();
        uint8_t operand = read8Bits();
        interpreter(operation, operand);
    }
}

void ConcurrentMusicPlayer::readNumberInstructions() {
    uint8_t firstNumberHalf = read8Bits();
    numberInstructions_ = static_cast<uint16_t>(firstNumberHalf) << 8;
    uint8_t secondNumberHalf = read8Bits();
    numberInstructions_ |= static_cast<uint16_t>(secondNumberHalf);
    numberInstructions_ -= 2;
    numberInstructions_ /= 2;
}

void ConcurrentMusicPlayer::interpreter(uint8_t instruction, uint8_t operand) {
    switch (instruction) {
        case Operations::dbt:
            dbt();
            break;

        case Operations::att:
            att(operand);
            break;

        case Operations::sgo:
            sgo(operand);
            break;

        case Operations::sar:
            sar();
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
        default:
            break;
    }
}

void ConcurrentMusicPlayer::dbt() {
}

void ConcurrentMusicPlayer::att(uint8_t operand) {
    afterWaitTime_ = SystemTimer::getTimer() + operand * DELAY_MS;
}

void ConcurrentMusicPlayer::sgo(uint8_t operand) {  // jouer une sonorité
    BuzzerController::playNote(operand);
}

void ConcurrentMusicPlayer::sar() {  // arrêter de jouer la sonorité
    BuzzerController::stopNote();
}

void ConcurrentMusicPlayer::dbc(uint8_t operand) {  // début de boucle
    loopAddress_ = currentAdress_;
    loopInstructionNumber_ = numberInstructions_;
    counter_ = operand + 1;
}

void ConcurrentMusicPlayer::fbc() {  // fin de boucle
    if (counter_ != 0) {
        currentAdress_ = loopAddress_;
        counter_--;
        numberInstructions_ = loopInstructionNumber_;
    }
}

void ConcurrentMusicPlayer::fin() {
    currentAdress_ -= (2 * numberInstructions_);
}

bool ConcurrentMusicPlayer::canPlay() {
    return startTrack_ && SystemTimer::getTimer() >= afterWaitTime_;
}

void ConcurrentMusicPlayer::setTrackPlayingStatus(bool trackPlaying) {
    startTrack_ = trackPlaying;
}
