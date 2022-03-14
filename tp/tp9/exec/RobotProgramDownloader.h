#include <memoire_24.h>
#include <usart.h>

class RobotProgramDownloader {
    public:
        RobotProgramDownloader();

        void acceptProgramData();

        bool receivedData();
    private:
        bool receivedData_;
        usart receptor_;
        Memoire24CXXX memory_;
        uint16_t totalBytes_;
};