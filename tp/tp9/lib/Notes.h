
#pragma once
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.h>
#include <counter.h>


class Notes {
	public:
		Notes();
        ~Notes() = default;
		void stopNote();
		void playNote(uint8_t note);

    private:
        CounterInterrupt counter_;
        usart transmitter_;
};


const uint16_t notes[37] = { 
    110,     //45
    116, //46
    123, //47
    130, //48
    138, //49
    146, //50
    155, //51
    164, //52
    174, //53
    184, //54
    195, //55
    207, //56
    220,     //57
    233, //58
    246, //59
    261, //60
    277, //61
    293, //62
    311, //63
    329, //64
    349, //65
    369, //66
    391, //67
    415, //68
    440,     //69
    466, //70
    493, //71
    523, //72
    554, //73
    587,  //74
    622, //75
    659, //76
    698, //77
    739, //78
    783, //79
    830, //80
    880      //81
}; 