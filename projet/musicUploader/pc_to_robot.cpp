#include <usart.h>
#include <RobotProgramDownloader.h>
#include <musicPlayerConstants.h>

int main() {
    // Size Indiana : 598 Bytes
    // Size Crazy : 582 Bytes
    usart::initialization();
    RobotProgramDownloader programmer(music::START_OF_MUSIC_ADDRESS + 598);
    programmer.acceptProgramData();
    
    return 0;
}