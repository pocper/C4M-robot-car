#include "servo.h"

#include <stdio.h>

#define BIT(m) (0x01 << (m))
#define BIT_CLEAR(p, m) ((p) &= ~(BIT(m)))
#define BIT_SET(p, m) ((p) |= (BIT(m)))
#define BIT_PUT(c, p, m) \
    (c ? BIT_SET(p, m) : BIT_CLEAR(p, m)) //將c蓋寫變數p的第m位元
#define CheckBit(data, bit) ((data & (1 << bit)) == (1 << bit))

#define ENABLE 1
#define DISABLE 0

uint16_t Servo_Value[11];
uint16_t Servo_U_Limit[11];
uint16_t Servo_L_Limit[11];
uint8_t Servo_Enable_Power;
uint16_t Servo_Enable_Channel;
// uint16_t servo_Enable_Protect;

void servo_init()
{
    UART1_init();

    for (int i = 0; i < sizeof(Servo_U_Limit) / sizeof(Servo_U_Limit[0]); i++)
    {
        Servo_L_Limit[i] = SERVO_LIMIT_MIN;
        Servo_U_Limit[i] = SERVO_LIMIT_MAX;
    }

    // servo_Enable_Protect = 0x7ff;
    Servo_Enable_Channel = 0x7ff;

    //  TODO
    //  將手臂歸位置特定位置
    //  先伸展到不會撞到任何牆壁
    //  再伸到比賽要求位置
}

void servo_Power(uint8_t Enable)
{
    Servo_Enable_Power = Enable;
    UART1_trm(RegAdd_Enable_Power, sizeof(Servo_Enable_Power), sizeof(uint8_t), &Servo_Enable_Power);
}

void servo_Enable(uint8_t channel, uint8_t Enable)
{
    printf("channel = %d En = %d\n", channel, Enable);
    BIT_PUT(Enable, Servo_Enable_Channel, channel);
    UART1_trm(RegAdd_Enable_Channel, sizeof(Servo_Enable_Channel), sizeof(uint16_t), &Servo_Enable_Channel);
}

void servo_update(uint8_t channel, float val)
{
    if (channel > 10)
        return;

    printf("channel = %d val = %f\n", channel, val);

    if (Servo_Enable_Power == DISABLE)
        servo_Power(ENABLE);

    if (CheckBit(Servo_Enable_Channel, channel) == DISABLE)
        servo_Enable(channel, ENABLE);

    float PWM;
    if (channel < 7)
    {
        PWM = Deg2PWM(val);
    }
    else if (channel < 11)
    {
        if (val == 0)
        {
            servo_Enable(channel, DISABLE);
            return;
        }
        else
            PWM = RPM2PWM(val);
    }

    if (PWM == 255)
        return;

    printf("PWM_Tick = %f\n", PWM);

    Servo_Value[channel] = PWM2Tick(PWM);

    if (Servo_Value[channel] == 65535)
        return;

    printf("Servo_Value = %d\n", Servo_Value[channel]);

    // UART1_trm(RegAdd_Multi_Val, sizeof(Servo_Value), sizeof(Servo_Value[0]), &Servo_Value);
    UART1_trm(RegAdd_Single_Val + channel, sizeof(Servo_Value[0]), sizeof(Servo_Value[0]), &Servo_Value[channel]);
}

uint16_t PWM2Tick(float PWM)
{
    /*
    0.925975 [ms] ->  90 等份
    1.480875 [ms] -> 205 等份
    2.035125 [ms] -> 320 等份
    */
    if (PWM > 2.5 || PWM < 0.5)
        return 65535;

    return 90 + (320 - 90) * (PWM - 0.925975) / (2.035125 - 0.925975);
}

float Deg2PWM(int8_t Degree)
{
    /*
    順時針是正方向
     -90.0 [Deg] -> 0.925975 [ms]
      00.0 [Deg] -> 1.480875 [ms]
     +90.0 [Deg] -> 2.035125 [ms]
    */

    if (Degree > 90 || Degree < -90)
        return 255;

    return 0.925975 + (2.035125 - 0.925975) * (Degree - (-90)) / 180; //單位[ms]
}

float RPM2PWM(int8_t RPM)
{
    uint8_t val = RPM2ControllableTable(RPM);
    return 0.5 + (float)(val) / 50;
}

uint8_t RPM2ControllableTable(int8_t RPM)
{
    // split how many pieces from 0 ~ 75 to 0.5ms ~ 2.5ms
    /*
     *  Value range : 0 ~ 75
     *  Frequency   : 50Hz per value
     *
     *  Value      PWM [ms]
     *    0    ->  0.5 [ms]
     *   75    ->  2.5 [ms]
     */

    uint8_t Controllable_val = 0;
    if (RPM <= 58 && RPM >= 48)
    {
        Controllable_val = 17.745 * RPM - 801 + 0.5;
        if (Controllable_val >= 69)
        {
            Controllable_val = 75;
        }
    }
    if (RPM <= 47 && RPM >= 0)
    {
        Controllable_val = 0.26 * RPM + 38 + 0.5;
    }
    if (RPM <= -1 && RPM >= -47)
    {
        Controllable_val = 0.26 * RPM + 38 + 0.5;
    }
    if (RPM <= -48 && RPM >= -58)
    {
        int ans = 17.745 * RPM + 845;
        if (ans < 0)
        {
            Controllable_val = 0;
        }
        else
        {
            Controllable_val = ans;
        }
    }

    return Controllable_val;
}
