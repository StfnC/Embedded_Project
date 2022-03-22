#define F_CPU 8000000
#include "RobotProgramDownloader.h"
#include <util/delay.h>
#include <usart.h>
#include <Notes.h>

void Partition();

int main() {
    DDRD |= 0xFF;
    usart tr = usart();
    Notes note = Notes();
    note.playNote(80);
};


// void Partition() {
//     DEBUG_PRINT_VARIABLE(0xAA);
//     Notes note = Notes();
//     DEBUG_PRINT_VARIABLE(0xBB);

//     note.playNote(80);
//     DEBUG_PRINT_VARIABLE(0xCC);

//     return;

//     // note.playNote(60);
//     // _delay_ms(600);
//     // note.stopNote();


//     // note.playNote(62);
//     // _delay_ms(600);
//     // note.stopNote();

//     // note.playNote(64);
//     // _delay_ms(1200);
//     // note.stopNote();

//     // note.playNote(62);
//     // _delay_ms(1200);
//     // note.stopNote();

//     // note.playNote(60);
//     // _delay_ms(600);
//     // note.stopNote();

//     // note.playNote(64);
//     // _delay_ms(600);
//     // note.stopNote();

//     // note.playNote(62);
//     // _delay_ms(600);
//     // note.stopNote();

//     // note.playNote(62);
//     // _delay_ms(600);
//     // note.stopNote();

//     // note.playNote(60);
//     // _delay_ms(2400);
//     // note.stopNote();

// };