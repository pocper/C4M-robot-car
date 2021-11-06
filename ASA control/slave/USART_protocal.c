#include "USART_protocal.h"

#include "pwm_def.h"
#include "PCA9685.h"

#include "src/isr.h"
#include "src/stdio.h"
#include "src/bits_op.h"

#include <stdlib.h>
#include <string.h>
#include <avr/io.h>

#define ERR_NFIND 255

uint8_t receiveData[maxReceieveBuffer];
uint8_t receiveDataLength = 0;

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

void DataDisplay()
{
    printf("receiveDataLength = %d\n", receiveDataLength);

    for (int i = 0; i < receiveDataLength; i++)
        printf("%d ", receiveData[i]);
    printf("\n");
}

void handle_rec_str()
{
    /*
     * Correct form
     * [M2S_HEADER] [RegAdd] [Bytes] [SingleBytes] [Data_1] ... [Data_Bytes] [M2S_ENDING]
     */

    uint8_t Idx_Header_1 = findStr(receiveDataLength, 0, M2S_HEADER, receiveData);
    if (Idx_Header_1 == ERR_NFIND)
        return;

    uint8_t RegAdd = receiveData[Idx_Header_1 + SLAVE_POS_REGADD];
    uint8_t Bytes = receiveData[Idx_Header_1 + SLAVE_POS_BYTES];

    if (!(Bytes == 1 || Bytes == 2 || Bytes == 22))
    {
        // ERROR 有些從Master -> Slave 的Header或Ending 會是M2S_HEADER +- 5 (171 169...)
        // printf("Bytes != 1 || Bytes != 2 | Bytes != 22\n");
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t SingleDataBytes = receiveData[Idx_Header_1 + SLAVE_POS_SINGLEBYTES];

    if (SingleDataBytes > sizeof(uint16_t))
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    uint8_t Idx_Header_2 = Idx_Header_1 + SLAVE_POS_SINGLEBYTES + Bytes + 1;

    if ((Idx_Header_2 + 1) > receiveDataLength)
        return;

    if (receiveData[Idx_Header_2] != M2S_ENDING)
    {
        receiveData[Idx_Header_1] = ERR_HEADER;
        return;
    }

    if (RegAdd == RegAdd_Clear_Buffer)
    {
        if (Bytes != 1)
        {
            receiveData[Idx_Header_1] = ERR_HEADER;
            return;
        }

        if (SingleDataBytes != sizeof(uint8_t))
        {
            receiveData[Idx_Header_1] = ERR_HEADER;
            return;
        }

        uint8_t Enable = receiveData[Idx_Header_1 + SLAVE_POS_DATA];
        if (Enable != Enable)
        {
            receiveData[Idx_Header_1] = ERR_HEADER;
            return;
        }

        if (receiveDataLength > 0)
        {
            memset(receiveData, 0, sizeof(receiveData));
            receiveDataLength = 0;
        }
    }
    else
    {
        uint8_t *Data = malloc(Bytes);
        if (Data == NULL)
            return;

        for (int dataNum = 0; dataNum < Bytes; dataNum++)
        {
            for (int Byte = 0; Byte < SingleDataBytes; Byte++)
            {
                Data[dataNum] = receiveData[Idx_Header_1 + SLAVE_POS_DATA + dataNum];
            }
        }

        PCA9685_mode(RegAdd, Bytes, SingleDataBytes, Data);
        free(Data);
    }

    memmove(receiveData + Idx_Header_1, receiveData + Idx_Header_2 + 1, receiveDataLength - Idx_Header_2);
    receiveDataLength -= Idx_Header_2 - Idx_Header_1 + 1;
}

void str_Remove()
{
    // #define M2S_HEADER 0xAA
    uint8_t Idx_Header_1 = findStr(receiveDataLength, 0, M2S_HEADER, receiveData);

    if ((Idx_Header_1 != ERR_NFIND) &&
        ((Idx_Header_1 == 0) ||
         (receiveDataLength > 1 && (Idx_Header_1 + 1) != receiveDataLength)))
        return;

    if (receiveDataLength > 0)
    {
        memset(receiveData, 0, receiveDataLength);
        receiveDataLength = 0;
    }
}

uint8_t DataLength()
{
    return receiveDataLength;
}