#include "timer.h"

void timer0_init()
{

    REGFPT(&TCCR0, 0x48, WGM01, 1); /*CTC*/
    REGFPT(&TCCR0, 0x07, CS00, 7);  /*除頻1024*/
    REGFPT(&TIMSK, 0x02, OCIE0, 1); /*致能中斷*/
    OCR0 = 255;

    //頻率：21.0900 [Hz]
    //時間： 0.0474 [s]
}

void timer1_init()
{
    REGFPT(&TCCR1A, 0x03, WGM10, 0); /*CTC*/
    REGFPT(&TCCR1B, 0x18, WGM12, 1); /*CTC*/
    REGFPT(&TCCR1B, 0x07, CS10, 5);  /*除頻1024*/
    REGFPT(&TIMSK, 0x10, OCIE1A, 1); /*致能Timer1_COMPA中斷*/
    OCR1A = 1079;

    //頻率：  5.00 [Hz]
    //時間：200.00 [ms]
}

void timer2_init()
{
    REGFPT(&TCCR2, 0x48, WGM01, 1); /*CTC*/
    REGFPT(&TCCR2, 0x07, CS00, 5);  /*除頻1024*/
    REGFPT(&TIMSK, 0x80, OCIE2, 1); /*致能中斷*/
    OCR2 = 107;
    //時間：0.01s
}