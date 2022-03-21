#define F_CPU 8000000

#include <debug.h>
#include <usart.h>
#include <util/delay.h>
#include <Notes.h>              


void Partition();

int main() {
    // DEBUG_INIT;
    // DDRA = 0XFF;
    // DDRB = 0XFF;
    DDRD = 0XFF;

    DEBUG_PRINT_VARIABLE(0xFF);

    _delay_ms(5000);

    DEBUG_PRINT_VARIABLE(0x0F);

    Partition();

    return 0;
};


void Partition() {
    DEBUG_PRINT_VARIABLE(0xAA);
    Notes note = Notes();
    DEBUG_PRINT_VARIABLE(0xBB);

    note.playNote(80); 
    DEBUG_PRINT_VARIABLE(0xCC);
    _delay_ms(2000);
    DEBUG_PRINT_VARIABLE(0xDD);
    note.stopNote();
    DEBUG_PRINT_VARIABLE(0xEE); 


    // note.playNote(60); 
    // _delay_ms(600);
    // note.stopNote();


    // note.playNote(62);
    // _delay_ms(600);
    // note.stopNote();

    // note.playNote(64);
    // _delay_ms(1200);
    // note.stopNote();

    // note.playNote(62);
    // _delay_ms(1200);
    // note.stopNote();

    // note.playNote(60);
    // _delay_ms(600);
    // note.stopNote();

    // note.playNote(64);
    // _delay_ms(600);
    // note.stopNote();

    // note.playNote(62);
    // _delay_ms(600);
    // note.stopNote();

    // note.playNote(62);
    // _delay_ms(600);
    // note.stopNote();

    // note.playNote(60);
    // _delay_ms(2400);
    // note.stopNote();

};