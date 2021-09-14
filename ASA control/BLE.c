#include "BLE.h"

#ifndef _ROBOT_H
#define _ROBOT_H
#include "Robot.h"
#endif

char receiveData[maxReceieveBuffer];
const char movement_key[] = "WASDQEZCR";

ISR(USART1_RX_vect)
{
    int receiveData_length = strlen(receiveData);

    receiveData[receiveData_length] = UDR1;
    receiveData_length++;
    receiveData[receiveData_length] = '\0';
}

//Sensor資料送收
// ISR(TIMER0_COMP_vect)
// {
//     static uint8_t DataStr[4] = {'@', 0, '@'};
//     static uint8_t counter = 0;
//     static uint8_t sensorData = 0;

//     //時間：0.1s 10Hz
//     if (counter == 10)
//     {
//         REGFGT(&PIND, 0xf0, 4, &sensorData);
//         DataStr[1] = sensorData + 48;
//         // printf("DataStr = %s\n", DataStr);
//         UARTM_trm(3, 9, 0, sizeof(DataStr), (void *)&DataStr, 1);
//         counter = 0;
//     }
//     counter++;
// }

ISR(TIMER0_COMP_vect)
{
    char *findHash_1 = strchr(receiveData, '#');
    char *findHash_2 = strchr(findHash_1 + 1, '#');

    char *findExclamation_1 = strchr(receiveData, '!');
    char *findExclamation_2 = strchr(findExclamation_1 + 1, '!');

    if (receiveData[0] != '\0')
        printf("receiveData = %s\n", receiveData);

    char *findUnderscore = strchr(findHash_1, '_');

    if (findHash_1 != NULL && findHash_2 != NULL)
    {
        if ((findHash_2 - findHash_1) == 6)
        {
            if (findUnderscore != NULL && (findUnderscore - findHash_1) == 2)
            {
                char ServoSentence[8];
                strncpy(ServoSentence, findHash_1, 7);
                ServoSentence[7] = '\0';
                // printf("ServoSentence = %s\n", ServoSentence);

                int param[2];
                sscanf(ServoSentence, "#%d_%d#", &param[0], &param[1]);
                // printf("param[0] = %d param[1] = %d\n", param[0], param[1]);
                Rotation_update(param[0], param[1]);
            }

            memmove(findHash_1, findHash_2 + 1, strlen(receiveData) - (findHash_2 + 1 - receiveData) + 1);
        }
        else
        {
            //清除'#'
            memmove(findHash_1, findHash_1 + 1, strlen(receiveData) - (findHash_1 - receiveData));
        }
    }

    if (findExclamation_1 != NULL && findExclamation_2 != NULL)
    {
        if ((findExclamation_2 - findExclamation_1) == 2)
        {
            char Dir = *(findExclamation_1 + 1);
            char *findDir = strchr(movement_key, Dir);

            if (findDir != NULL)
            {
                Movement_condition(findDir - movement_key);
            }

            memmove(findExclamation_1, findExclamation_2 + 1, strlen(receiveData) - (findExclamation_2 - receiveData));
        }
    }

    if (strlen(receiveData) > 0)
    {
        if (findHash_1 != NULL && (findHash_1 - receiveData) == strlen(receiveData))
        {
            //清除'#'
            memmove(findHash_1, findHash_1 + 1, strlen(receiveData) - (findHash_1 - receiveData));
        }

        //清除字串 若'#'之後找不到'_'
        if (strchr(findHash_1, '_') == NULL)
        {
            memset(receiveData, 0, sizeof(receiveData));
        }
    }
}

void UART_init()
{
    //設定UART通訊包率
    uint16_t baud = F_CPU / 16 / UARTBAUD - 1;
    UBRR1H = (uint8_t)(baud >> 8);
    UBRR1L = (uint8_t)baud;

    //設定RX/TX interrupt - RX ENABLE
    UCSR1B |= (1 << RXCIE1);

    //設定RX/TX 致能
    UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
}