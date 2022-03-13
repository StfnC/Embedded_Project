
#include <avr/interrupt.h>

enum class InterruptMode {
    LowLevelInterrupt,
    AnyEdgeInterrupt,
    FallingEdgeInterrupt,
    RisingEdgeInterrupt
};

class ButtonInterrupt {
   public:
    ButtonInterrupt(uint8_t interruptNumber, InterruptMode mode);
    ~ButtonInterrupt() {}

   private:
    uint8_t eicraValue_;
    uint8_t eimskValue_;
};
