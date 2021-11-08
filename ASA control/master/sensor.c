#include "pwm_def.h"
#include "global_def.h"

#include "sensor.h"
#include "USART.h"
#include "timer.h"

#include "c4mlib/C4MBios/macro/src/bits_op.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"

#include <avr/io.h>
#include <stdio.h>

ISR(TIMER2_COMP_vect)
{
    static uint8_t counter = 0;

    //時間：0.1s 10Hz
    if (counter == 10)
    {
        uint16_t sensorData = sensor_rec();

        UART0_buf_trm(SENSOR_HEADER);

        //資料高位元組先送 -> 由高到低送
        for (int Byte = sizeof(sensorData); Byte > 0; Byte--)
            UART0_buf_trm(sensorData >> (8 * (Byte - 1)));
        UART0_buf_trm(SENSOR_ENDING);

        counter = 0;
    }
    counter++;
}

void sensor_init()
{
    timer2_init();

    sensorA_init();
    sensorB_init();
    // sensorC_init();
    sensorD_init();
    sensorE_init();
    sensorF_init();
}

void sensorA_init()
{
    // Sensor_A1:A3
    // PE2:PE4
    REGFPT(&DDRE, 0x1c, 2, 0);
}

void sensorB_init()
{
    // Sensor_B1
    // PD7
    REGFPT(&DDRD, 0x80, 7, 0);

    // Sensor_B2:B3
    // PF0:PF1
    REGFPT(&DDRF, 0x03, 0, 0);
}

void sensorC_init()
{
    // Sensor_C1:C3
    // PE5:PE7
    REGFPT(&DDRE, 0xe0, 5, 0);
}

void sensorD_init()
{
    // Sensor_D1:3
    // PB4:PB6
    REGFPT(&DDRB, 0x70, 4, 0);
}

void sensorE_init()
{
    // Sensor_E1:E2
    // PF2:PF3
    REGFPT(&DDRF, 0x0c, 2, 0);

    // Sensor_E3
    // PB7
    REGFPT(&DDRB, 0x80, 7, 0);
}

void sensorF_init()
{
    // Sensor_F1_F3
    // PD4:PD6
    REGFPT(&DDRD, 0x70, 4, 0);
}

uint16_t sensor_rec()
{

    /*
     * sensorA
     * sensorB
    //  * sensorC -> Error PIN E7 cannot receive
     * sensorD
     * sensorE
     * sensorF
     */

    //          有接收到
    // 向上      0b001
    // 向前      0b010
    // 向左/右   0b100

    //資料由高到低儲存 PX3:PX1
    uint8_t sensor[sensor_num];
    uint8_t temp;

    // sensorA1:A3 | PE2:PE4
    temp = 0;
    REGFGT(&PINE, 0x1c, 2, &temp);
    sensor[0] = temp;

    // sensorB1:B3 | PD7 + PF0:PF1
    temp = 0;
    REGFGT(&PIND, 0x80, 7, &temp);
    sensor[1] = temp;
    REGFGT(&PINF, 0x03, 0, &temp);
    sensor[1] += temp << 1;

    // // sensorC1:C3 | PE5:PE7
    // REGFGT(&PINE, 0xe0, 5, &temp);
    // sensor[2] = temp;

    // sensorD1:D3 | PB4:PB6
    temp = 0;
    REGFGT(&PINB, 0x70, 4, &temp);
    sensor[2] = temp;

    // sensorE1:E3 | PF2:PF3 + PB7
    temp = 0;
    REGFGT(&PINF, 0x0c, 2, &temp);
    sensor[3] = temp;
    REGFGT(&PINB, 0x80, 7, &temp);
    sensor[3] += temp << 2;

    // sensorF1:F3 | PD4:PD6
    temp = 0;
    REGFGT(&PIND, 0x70, 4, &temp);
    sensor[4] = temp;

    // 111 111 111 111 111
    uint16_t Data = 0;
    for (int i = 0; i < sensor_num; i++)
    {
        Data += sensor[i] << 3 * (4 - i);
    }

    return Data;
}