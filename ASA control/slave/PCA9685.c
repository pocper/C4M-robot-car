#include "PCA9685.h"
#include "src/stdio.h"

#define SERVO_VAL_INIT 205

uint16_t Servo_Output_Value[16];
uint16_t Servo_Value[16];
uint16_t Servo_U_Limit[16] = {338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338};
uint16_t Servo_L_Limit[16] = {72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72};
uint16_t Servo_Enable_Channel;
uint8_t Servo_Enable_Power;
uint16_t Servo_Enable_Protect;

void PCA9685_init()
{

    SetBit(DDRD, 7);
    ClearBit(PORTD, 7); // Set Low: Open Power to Servo by Relay

    PCA9685_Init(0, 50);

    for (int i = 0; i < Servo_num; i++)
    {
        Servo_Output_Value[i] = SERVO_VAL_INIT;
        PCA9685_ServoSet(i, Servo_Output_Value[i]);
    }

    SetBit(DDRB, 0);
    ClearBit(PORTB, 0); // PCA9685 Servo Output Enable

    SetBit(PORTD, 7); // Set High: Close Power to Servo by Relay
}

void PCA9685_update()
{
    // 依命令控制伺服機電源總開關
    if (Servo_Enable_Power == 0)
        SetBit(PORTD, 7); // Set High: Close Power to Servo by Relay
    else
        ClearBit(PORTD, 7); // Set Low: Open Power to Servo by Relay

    // 依上下限設定及禁致能狀態更新伺服機真實輸出值
    for (int i = 0; i < 16; i++)
    {
        if (Servo_Value[i] < Servo_L_Limit[i])
            Servo_Output_Value[i] = Servo_L_Limit[i] + MIN_POSITION;
        else if (Servo_Value[i] > Servo_U_Limit[i])
            Servo_Output_Value[i] = Servo_U_Limit[i] + MIN_POSITION;
        else
            Servo_Output_Value[i] = Servo_Value[i] + MIN_POSITION;

        if (CheckBit(Servo_Enable_Channel, i) == 0)
            Servo_Output_Value[i] = 0;

        PCA9685_Set(i, Servo_Output_Value[i]);
    }
}

void PCA9685_mode(uint8_t RegAdd, uint8_t Bytes, uint8_t SingleDataBytes, void *Data_p)
{
    uint8_t *data_p = Data_p;
    uint8_t dataCount;

    if (RegAdd >= RegAdd_Single_Val && RegAdd <= RegAdd_Single_Val + Servo_num)
    {
        if (Bytes != sizeof(uint16_t))
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        Servo_Value[RegAdd - RegAdd_Single_Val] = (data_p[0] << 8) + data_p[1];
    }

    switch (RegAdd)
    {
    case RegAdd_Multi_Val:
        if (Bytes != 22)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        dataCount = (float)(Bytes) / SingleDataBytes;

        for (int dataNum = 0; dataNum < dataCount; dataNum++)
        {
            Servo_Value[dataNum] = 0;
            for (int Byte = 0; Byte < SingleDataBytes; Byte++)
            {
                //高位元先處理
                Servo_Value[dataNum] += (uint16_t)(data_p[dataNum * SingleDataBytes + Byte]) << 8 * (SingleDataBytes - Byte - 1);
            }
        }
        break;

    case RegAdd_L_Lim:
        if (Bytes != 22)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        dataCount = (float)(Bytes) / SingleDataBytes;

        for (int dataNum = 0; dataNum < dataCount; dataNum++)
        {
            Servo_L_Limit[dataNum] = 0;
            for (int Byte = 0; Byte < SingleDataBytes; Byte++)
            {
                //高位元先處理
                Servo_L_Limit[dataNum] += (uint16_t)(data_p[dataNum * SingleDataBytes + Byte]) << 8 * (SingleDataBytes - Byte - 1);
            }
        }

        break;

    case RegAdd_U_Lim:
        if (Bytes != 22)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        dataCount = (float)(Bytes) / SingleDataBytes;

        for (int dataNum = 0; dataNum < dataCount; dataNum++)
        {
            Servo_U_Limit[dataNum] = 0;
            for (int Byte = 0; Byte < SingleDataBytes; Byte++)
            {
                Servo_U_Limit[dataNum] += (uint16_t)(data_p[dataNum * SingleDataBytes + Byte]) << 8 * (SingleDataBytes - Byte - 1);
            }
        }

        break;

    case RegAdd_Enable_Channel:
        if (Bytes != 2)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        Servo_Enable_Channel = 0;
        for (int Byte = 0; Byte < SingleDataBytes; Byte++)
        {
            Servo_Enable_Channel += (uint16_t)(data_p[Byte]) << 8 * (SingleDataBytes - Byte - 1);
        }

        break;

    case RegAdd_Enable_Power:
        if (Bytes != 1)
            return;

        if (SingleDataBytes != sizeof(uint8_t))
            return;

        Servo_Enable_Power = data_p[0];
        break;

    case RegAdd_Enable_Protect:

        if (Bytes != 2)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;

        Servo_Enable_Protect = 0;
        for (int Byte = 0; Byte < SingleDataBytes; Byte++)
        {
            Servo_Enable_Protect += (uint16_t)(data_p[Byte]) << 8 * (SingleDataBytes - Byte - 1);
        }
        break;

    case RegAdd_Single_Val:
        if (Bytes != 2)
            return;

        if (SingleDataBytes != sizeof(uint16_t))
            return;
    }
}