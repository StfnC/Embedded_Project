#include <memoire_24.h>
#include <usart.h>

class RobotProgramDownloader {
    public:
        RobotProgramDownloader();

        void acceptProgramData();
    private:
        usart receptor_;
        Memoire24CXXX memory_;
        uint16_t totalBytes_;

        void writeTotalBytes();
        void writeProgramToMemory();
};