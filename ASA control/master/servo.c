#include "servo.h"

#include <stdio.h>

#define BIT(m) (0x01 << (m))
#define BIT_CLEAR(p, m) ((p) &= ~(BIT(m)))
#define BIT_SET(p, m) ((p) |= (BIT(m)))
#define BIT_PUT(c, p, m) \
    (c ? BIT_SET(p, m) : BIT_CLEAR(p, m)) //將c蓋寫變數p的第m位元

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
    // servo_Power(ENABLE);
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
    printf("Servo_Enable_Channel = %d\n", Servo_Enable_Channel);
    BIT_PUT(Enable, Servo_Enable_Channel, channel);
    UART1_trm(RegAdd_Enable_Channel, sizeof(Servo_Enable_Channel), sizeof(uint16_t), &Servo_Enable_Channel);
}

uint8_t servo_update(uint8_t channel, float val)
{
    printf("val = %f\n", val);

    Servo_Enable_Power = ENABLE;
    servo_Power(ENABLE);
    servo_Enable(channel, ENABLE);
    float PWM;
    if (channel < 7)
        PWM = Deg2PWM(val);
    else if (channel < 11)
        PWM = RPM2PWM(val);
    else
        PWM = 255;

    if (PWM == 255)
        return 255;

    printf("PWM = %f\n", PWM);
    Servo_Value[channel] = PWM2Tick(PWM);

    if (Servo_Value[channel] == 65535)
        return 255;

    // Servo_Value[channel] = PWM2Tick(val);

    printf("Servo_Value = %d\n", Servo_Value[channel]);

    UART1_trm(RegAdd_Val, sizeof(Servo_Value), sizeof(Servo_Value[0]), &Servo_Value);

    return 0;
}

uint16_t PWM2Tick(float PWM)
{
    /*
    0.50 [ms] ->   0 等份
    0.85 [ms] ->  72 等份
    2.15 [ms] -> 338 等份
    2.50 [ms] -> 410 等份
    */
    if (PWM > 2.5 || PWM < 0.5)
        return 65535;

    return (PWM - 0.5) / (2.5 - 0.5) * (410 - 0) + 0;
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

uint8_t RPM2PWM(int8_t RPM)
{
    if (RPM > 58 || RPM < -58)
        return 255;

    uint8_t PWM = 0;
    if (RPM <= 58 && RPM >= 48)
    {
        PWM = 17.745 * RPM - 801 + 0.5;
        if (PWM >= 69)
        {
            PWM = 75;
        }
    }
    if (RPM <= 47 && RPM >= 0)
    {
        PWM = 0.26 * RPM + 38 + 0.5;
    }
    if (RPM <= -1 && RPM >= -47)
    {
        PWM = 0.26 * RPM + 38 + 0.5;
    }
    if (RPM <= -48 && RPM >= -58)
    {
        int ans = 17.745 * RPM + 845;
        if (ans < 0)
        {
            RPM = 0;
        }
        else
        {
            RPM = ans;
        }
    }
    return PWM;
}
