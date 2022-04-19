#define F_CPU 8000000

#include <MotorsController.h>
#include <usart.h>
#include <BuzzerController.h>
#include <Interpreter.h>
#include <avr/io.h>

int main() {
    usart::initialization();
    MotorsController::initialization();
    BuzzerController::initBuzzer();
    Interpreter interpreter;
    interpreter.interpretCode();

    return 0;
};
