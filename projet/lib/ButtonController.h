#pragma once

class ButtonController {
    public:
        static void init();
        static bool isBreadButtonPressed();
        static bool isSmallButtonPressed();
        static void setBreadButtonPressed(bool pressed);
        static void setSmallButtonPressed(bool pressed);

    private:
        static bool breadButtonPressed_;
        static bool smallButtonPressed_;
};
