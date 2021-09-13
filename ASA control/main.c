#ifndef _C4MLIB_H
#define _C4MLIB_H
#include "c4mlib.h"
#endif

#ifndef _SERVO_H
#define _SERVO_H
#include "servo.h"
#endif

#ifndef _BLE_H
#define _BLE_H
#include "BLE.h"
#endif

int main()
{
    C4M_DEVICE_set();
    UART_init();

    timer0_init();
    timer1_init();
    timer2_init();
    timer3_init();

    sei();
    printf("Start\n");

    while (1)
    {
        ;
    }

    return 0;
}
