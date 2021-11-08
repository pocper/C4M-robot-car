#include "pwm_def.h"
#include "global_def.h"

#include "USART_protocal.h"
#include "car.h"
#include "servo.h"

#include "c4mlib/C4MBios/macro/src/bits_op.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"

#include <string.h>
#include <stdio.h>

#define ERR_NFIND 255

uint8_t receiveData[maxReceieveBuffer];
uint8_t receiveDataLength = 0;

char movement_key[] = "WASDQEZCRV";

ISR(USART0_RX_vect)
{
    receiveData[receiveDataLength] = UDR0;
    receiveDataLength++;
}

uint8_t findStr(uint8_t Length, uint8_t start_idx, uint8_t find, void *Data_p)
{
    uint8_t *data_p = Data_p;
    for (int idx = start_idx; idx < Length; idx++)
    {
        if (data_p[idx] == find)
            return idx;
    }
    return ERR_NFIND;
}

void servo_str_split()
{
    /*
     * Correct form
     * [SERVO_HEADER] [RegAdd] [Data] [SERVO_ENDING]
     */

    uint8_t Idx_Header_1 = findStr(receiveDataLength, 0, SERVO_HEADER, receiveData);
    if (Idx_Header_1 == ERR_NFIND)
        return;

    uint8_t Idx_Header_2 = Idx_Header_1 + SERVO_POS_ENDING;

    if (receiveData[Idx_Header_2] != SERVO_ENDING)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t StrLength = Idx_Header_2 - Idx_Header_1;


    if (StrLength != (SERVO_POS_ENDING - SERVO_POS_HEADER))
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t RegAdd = receiveData[Idx_Header_1 + SERVO_POS_REGADD];
    uint8_t Data = receiveData[Idx_Header_1 + SERVO_POS_DATA];

    if (Data > (128 + 90) || Data < (128 - 90))
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    if (RegAdd < 7)
    {
        Rotation_update(RegAdd, (int16_t)(Data)-128);
    }
    else if (RegAdd < Servo_num)
    {
        Movement_update(RegAdd, (int16_t)(Data)-128);
    }
    else
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    memmove(receiveData + Idx_Header_1, receiveData + Idx_Header_2 + 1, receiveDataLength - Idx_Header_2);
    receiveDataLength -= StrLength + 1;
}

void servo_enable_str_split()
{
    /*
     * Correct form
     * [SERVO_EN_HEADER] [RegAdd] [Data] [SERVO_EN_ENDING]
     */

    uint8_t Idx_Header_1 = findStr(receiveDataLength, 0, SERVO_EN_HEADER, receiveData);
    if (Idx_Header_1 == ERR_NFIND)
        return;

    uint8_t Idx_Header_2 = Idx_Header_1 + SERVO_EN_POS_ENDING;
    if (receiveData[Idx_Header_2] != SERVO_EN_ENDING)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t StrLength = Idx_Header_2 - Idx_Header_1;

    if (StrLength != (SERVO_EN_POS_ENDING - SERVO_EN_POS_HEADER))
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t RegAdd = receiveData[Idx_Header_1 + SERVO_EN_POS_REGADD];

    if (RegAdd > (Servo_num - 1))
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t Data = receiveData[Idx_Header_1 + SERVO_EN_POS_DATA];
    if (Data > ENABLE)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    servo_Enable(RegAdd, Data);

    memmove(receiveData + Idx_Header_1, receiveData + Idx_Header_2 + 1, receiveDataLength - Idx_Header_2);
    receiveDataLength -= StrLength + 1;
}

void servo_enable_str_concat(uint8_t RegAdd, uint8_t Enable)
{
    receiveData[receiveDataLength + SERVO_EN_POS_HEADER] = SERVO_EN_HEADER;
    receiveData[receiveDataLength + SERVO_EN_POS_REGADD] = RegAdd;
    receiveData[receiveDataLength + SERVO_EN_POS_DATA] = Enable;
    receiveData[receiveDataLength + SERVO_EN_POS_ENDING] = SERVO_EN_ENDING;

    receiveDataLength += 4;
}

void movement_str_split()
{
    /*
     * Correct form
     * [MOVEMENT_HEADER] [Data] [MOVEMENT_ENDING]
     */

    uint8_t Idx_Header_1 = findStr(receiveDataLength, 0, MOVEMENT_HEADER, receiveData);
    if (Idx_Header_1 == ERR_NFIND)
        return;

    uint8_t Idx_Header_2 = Idx_Header_1 + MOVEMENT_POS_ENDING;
    if (receiveData[Idx_Header_2] != MOVEMENT_ENDING)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t StrLength = Idx_Header_2 - Idx_Header_1;

    if (StrLength != 2)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t Data = receiveData[Idx_Header_1 + MOVEMENT_POS_DATA];

    char idx_Dir = findStr(sizeof(movement_key), 0, Data, movement_key);

    if (idx_Dir == ERR_NFIND)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    Movement_condition(idx_Dir);

    memmove(receiveData + Idx_Header_1, receiveData + Idx_Header_2 + 1, receiveDataLength - Idx_Header_2);
    receiveDataLength -= StrLength + 1;
}

// TODO LIST 我沒有替指令以外的清除 因為基本不會傳到指令以外的資料
void str_Remove()
{
    uint8_t Idx_Header_1, Idx_Header_2;
    uint8_t chk_sum = 0;

    // #define SERVO_HEADER 0xB0
    Idx_Header_1 = findStr(receiveDataLength, 0, SERVO_HEADER, receiveData);
    chk_sum += (Idx_Header_1 != ERR_NFIND);

    if (Idx_Header_1 != ERR_NFIND)
    {
        Idx_Header_2 = findStr(receiveDataLength, Idx_Header_1 + 1, SERVO_ENDING, receiveData);
        if ((Idx_Header_2 - Idx_Header_1) > (SERVO_POS_ENDING - SERVO_POS_HEADER))
            receiveData[Idx_Header_1] = ERR_HEADER;
    }

    // #define SERVO_EN_HEADER 0xB1
    Idx_Header_1 = findStr(receiveDataLength, 0, SERVO_EN_HEADER, receiveData);
    chk_sum += (Idx_Header_1 != ERR_NFIND);

    if (Idx_Header_1 != ERR_NFIND)
    {
        Idx_Header_2 = findStr(receiveDataLength, Idx_Header_1 + 1, SERVO_EN_ENDING, receiveData);
        if ((Idx_Header_2 - Idx_Header_1) > (SERVO_EN_POS_ENDING - SERVO_EN_POS_HEADER))
            receiveData[Idx_Header_1] = ERR_HEADER;
    }

    // #define MOVEMENT_HEADER 0xB2
    Idx_Header_1 = findStr(receiveDataLength, 0, MOVEMENT_HEADER, receiveData);
    chk_sum += (Idx_Header_1 != ERR_NFIND);

    if (Idx_Header_1 != ERR_NFIND)
    {
        Idx_Header_2 = findStr(receiveDataLength, Idx_Header_1 + 1, MOVEMENT_ENDING, receiveData);
        if ((Idx_Header_2 - Idx_Header_1) > (MOVEMENT_POS_ENDING - MOVEMENT_POS_HEADER))
            receiveData[Idx_Header_1] = ERR_HEADER;
    }

    if (chk_sum == 0)
    {
        memset(receiveData, 0, sizeof(receiveData));
        receiveDataLength = 0;
        return;
    }

    Idx_Header_1 = findStr(receiveDataLength, 0, ERR_HEADER, receiveData);
    if (Idx_Header_1 == ERR_NFIND)
        return;

    Idx_Header_2 = findStr(receiveDataLength, Idx_Header_1 + 1, ERR_HEADER, receiveData);
    if (Idx_Header_2 == ERR_NFIND)
        return;

    memmove(receiveData + Idx_Header_1, receiveData + Idx_Header_2 + 1, Idx_Header_2 - Idx_Header_1 + 1);
    receiveDataLength -= Idx_Header_2 - Idx_Header_1 + 1;
}

void DataDisplay()
{
    printf("receiveDataLength = %d\n", receiveDataLength);

    for (int i = 0; i < receiveDataLength; i++)
        printf("%d ", receiveData[i]);
    printf("\n");
}

uint8_t DataLength()
{
    return receiveDataLength;
}