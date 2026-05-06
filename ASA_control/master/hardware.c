#include "hardware.h"
#include "USART.h"
#include "c4mlib/ServiceProvi/asauart/src/asauart_master_card.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"
#include <util/delay.h>
#include <stdio.h>

#define ENABLE 1
#define DISABLE 0

#define ExtensionBoard_Mode 0
#define ExtensionBoard_UartID 128
#define servo_num 16

uint16_t Servo_Value[servo_num] = {205, 205, 205, 205, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint16_t Servo_Channel_Enable = 0x000f;
uint8_t Servo_PowerRelaySwitch = 0;

UARTMStr_t uart_str_p = UART1REGPARA;
Wheel wheelVal = {-1, 1, -1, 1};
// WheelMid wheelMid = {194, 192, 193, 194};
WheelForward wheelForward = {244, 267, 254, 229};
WheelBackward wheelBackward = {162, 154, 115, 136};
uint8_t RPM = 40;

#define ERR_NFIND 255
char movement_key[] = "WASDQEG";
uint8_t receiveData;

ISR(USART0_RX_vect)
{
    receiveData = UDR0;
    Movement_update();
}

uint8_t findStr(uint8_t find, void *Data_p)
{
    uint8_t *data_p = (uint8_t *)Data_p;
    for (int idx = 0; idx < sizeof(movement_key) - 1; idx++)
    {
        if (data_p[idx] == find)
            return idx;
    }
    return ERR_NFIND;
}

void Movement_condition(uint8_t Dir)
{
    switch (Dir)
    {
    case forward:
        wheelVal.left_front = -1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = 1;
        break;

    case left:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;

    case backward:
        wheelVal.left_front = 1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = -1;
        break;

    case right:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;

    case rotate_ccw:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;

    case rotate_cw:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;
    }
}

/*
        ---front---
        ___________
2 -     |         |   - 0
        |         |
        |         |
        |         |
        |         |
3  -    |_________|   - 1
        ---back---
*/

void Movement_update()
{
    uint8_t idx = findStr(receiveData, (void *)&movement_key);
    if (idx == ERR_NFIND)
        return;

    if (receiveData == 'G')
    {
        servo_Power(DISABLE);
        return;
    }

    Movement_condition(idx);
    servo_update();
}

void servo_init()
{
    servo_Power(DISABLE);
    UARTM0_trm(&uart_str_p, ExtensionBoard_Mode, ExtensionBoard_UartID, 4, sizeof(Servo_Channel_Enable), &Servo_Channel_Enable);
}

void servo_Power(uint8_t Enable)
{
    Servo_PowerRelaySwitch = Enable;
    UARTM0_trm(&uart_str_p, ExtensionBoard_Mode, ExtensionBoard_UartID, 5, sizeof(Servo_PowerRelaySwitch), &Servo_PowerRelaySwitch);
}

void servo_update()
{
    servo_Power(DISABLE);

    // Servo_Value[0] = PWM2Tick(RPM2PWM(wheelVal.right_front));
    // Servo_Value[1] = PWM2Tick(RPM2PWM(wheelVal.right_rear));
    // Servo_Value[2] = PWM2Tick(RPM2PWM(wheelVal.left_front));
    // Servo_Value[3] = PWM2Tick(RPM2PWM(wheelVal.left_rear));
    /*
    // 靜止點
    // 191 ~ 194
    // 194 ~ 197

    // 數值越小過靜止點為逆時鐘
    // 數值越大過靜止點為順時鐘

    // 定義 順時針為正方向
    // 第一顆伺服機
    // + 0 [rpm] => 191 ~ 194
    // 轉一圈時間 => Tick
    // 1.102 [s] => 100
    // 1.088 [s] => 110
    // 1.160 [s] => 120
    // 1.147 [s] => 130
    // 1.134 [s] => 140
    // 1.160 [s] => 150
    // 1.280 [s] => 160
    // 1.866 [s] => 170
    // 1.918 [s] => 171
    // 1.994 [s] => 172
    // 2.084 [s] => 173
    // 2.316 [s] => 174
    // 2.341 [s] => 175
    // 2.540 [s] => 176
    // 2.751 [s] => 177
    // 2.880 [s] => 178
    // 3.018 [s] => 179
    // 3.209 [s] => 180
    // 3.418 [s] => 181
    // 3.719 [s] => 182
    // 4.129 [s] => 183
    // 4.503 [s] => 184
    // 5.079 [s] => 185
    // 5.897 [s] => 186
    // 8.441 [s] => 187
    // 8.937 [s] => 188
    // 無限大(不穩定) [s] => 189
    // 無限大         [s] => 190
    // 無限大         [s] => 191
    // 無限大         [s] => 192
    // 12.786 [s] => 193
    //  8.931 [s] => 194
    //  7.319 [s] => 195
    //  5.174 [s] => 196
    //  5.036 [s] => 197
    //  4.358 [s] => 198
    //  3.833 [s] => 199
    //  3.323 [s] => 200
    //  2.955 [s] => 201
    //  2.930 [s] => 202
    //  2.424 [s] => 203
    //  2.244 [s] => 204
    //  2.151 [s] => 205
    //  2.114 [s] => 206
    //  1.832 [s] => 207
    //  1.805 [s] => 208
    //  1.729 [s] => 209
    //  1.619 [s] => 210
    //  1.218 [s] => 220
    //  1.178 [s] => 230
    //  1.124 [s] => 240
    //  1.090 [s] => 250
    //  1.079 [s] => 260
    //  1.082 [s] => 270
    //  1.073 [s] => 280
    //  1.081 [s] => 290
    //  1.061 [s] => 300
    */

    /* 靜止點
                                                        ---front---
                                                        ___________
            191 ~ 194 | 195 (不穩定) | 中點 193  2 -     |         |   - 0 193 ~ 197 | 192 (不穩定) | 中點 194
                                                        |         |
                                                        |         |
                                                        |         |
                                                        |         |
            193 ~ 196 | 192 (不穩定) | 中點 194  3  -    |_________|   - 1 192 ~ 196 | 197 (不穩定) | 中點 192
                                                        ---back---
    */

    Servo_Value[0] = (wheelVal.right_front > 0) ? wheelForward.right_front : wheelBackward.right_front;
    Servo_Value[1] = (wheelVal.right_rear > 0) ? wheelForward.right_rear : wheelBackward.right_rear;
    Servo_Value[2] = (wheelVal.left_front > 0) ? wheelForward.left_front : wheelBackward.left_front;
    Servo_Value[3] = (wheelVal.left_rear > 0) ? wheelForward.left_rear : wheelBackward.left_rear;
    printf("%d %d %d %d\n", wheelVal.right_front, wheelVal.right_rear, wheelVal.left_front, wheelVal.left_rear);
    printf("%d %d %d %d\n\n", Servo_Value[0], Servo_Value[1], Servo_Value[2], Servo_Value[3]);
    UARTM0_trm(&uart_str_p, ExtensionBoard_Mode, ExtensionBoard_UartID, 1, sizeof(Servo_Value), &Servo_Value);
    _delay_ms(10);
    servo_Power(ENABLE);
}

uint16_t PWM2Tick(float PWM)
{
    /*
    0.925975 [ms] ->  90 等份
    1.480875 [ms] -> 205 等份
    2.035125 [ms] -> 320 等份
    */

    return 90 + (320 - 90) * (PWM - 0.925975) / (2.035125 - 0.925975);
}

float RPM2PWM(int8_t RPM)
{
    float val = RPM2ControllableTable(RPM);
    return 0.5 + val / 37.5;
}

float RPM2ControllableTable(int8_t RPM)
{
    // split how many pieces from 0 ~ 75 to 0.5ms ~ 2.5ms
    /*
     *  Value range : 0 ~ 75
     *  Frequency   : 500Hz per value
     *
     *  Value      PWM [ms]
     *    0    ->  0.5 [ms]
     *   75    ->  2.5 [ms]
     */

    float Controllable_val = 0;

    if (RPM <= 58 && RPM >= 48)
    {
        Controllable_val = 0.254 * RPM * RPM - 24.291 * RPM + 628.47;
    }
    else if (RPM < 48 && RPM >= 0)
    {
        Controllable_val = 0.189 * RPM + 38;
    }
    else if (RPM < 0 && RPM >= -46)
    {
        Controllable_val = 0.26 * RPM + 38;
    }
    else if (RPM < -46 && RPM >= -47)
    {
        Controllable_val = 17.745 * RPM + 845;
    }
    else if (RPM < -47 && RPM >= -58)
    {
        Controllable_val = 0;
    }

    return Controllable_val;
}
