#include <usart.h>
#include <RobotProgramDownloader.h>

int main() {
    usart::initialization();
    RobotProgramDownloader programmer;
    programmer.acceptProgramData();
    
    return 0;
}