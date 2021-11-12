#include <sensor.h>
#include <pwm_def.h>
#include <global_def.h>

// Windows
#include <stdio.h>
#include <string.h>

// Linux
#include <sys/unistd.h>

#define ERROR 255

void UART_sensor_rec(int fd)
{
    char receiveBuffer[10];
    char bytes_num = read(fd, &receiveBuffer, sizeof(receiveBuffer));

    /*Test Receive Data
    for (int i = 0; i < bytes_num; i++)
        printf("%c", receiveBuffer[i]);
    printf("\n");
    */

    char sensor_sentence_startIdx = findCharIdx(SENSOR_HEADER, receiveBuffer);

    if (sensor_sentence_startIdx == ERROR)
        return;

    char sensor_sentence_endIdx = findCharIdx(SENSOR_ENDING, receiveBuffer);
    if (sensor_sentence_endIdx == ERROR)
        return;

    //[SENSOR_HEADER][Data_H][Data_L][SENSOR_ENDING]
    //       F3         01      01          F4

    int sensorData = 0;
    if ((sensor_sentence_endIdx - sensor_sentence_startIdx) == 4)
    {
        sensorData = receiveBuffer[sensor_sentence_startIdx] << 8;
        sensorData += receiveBuffer[sensor_sentence_startIdx + 1];
    }

    updateSensor(sensorData);
}

void updateSensor(int data)
{
    if (CheckBit(data, 14))
        printf("Sensor_right_behind_ground Detected");
    else
        printf("Sensor_right_behind_ground\n");

    if (CheckBit(data, 13))
        printf("Sensor_right_behind_right Detected\n");
    else
        printf("Sensor_right_behind_right Undetected\n");

    if (CheckBit(data, 12))
        printf("Sensor_right_behind_behind Detected\n");
    else
        printf("Sensor_right_behind_behind Undetected\n");

    if (CheckBit(data, 11))
        printf("Sensor_left_behind_ground Detected\n");
    else
        printf("Sensor_left_behind_ground Undetected\n");

    if (CheckBit(data, 10))
        printf("Sensor_left_behind_left Detected\n");
    else
        printf("Sensor_left_behind_left Undetected\n");

    if (CheckBit(data, 9))
        printf("Sensor_left_behind_behind Detected\n");
    else
        printf("Sensor_left_behind_behind Undetected\n");

    if (CheckBit(data, 8))
        printf("Sensor_right_front_ground Detected\n");
    else
        printf("Sensor_right_front_ground Undetected\n");

    if (CheckBit(data, 7))
        printf("Sensor_right_front_right Detected\n");
    else
        printf("Sensor_right_front_right Undetected\n");

    if (CheckBit(data, 6))
        printf("Sensor_right_front_front Detected\n");
    else
        printf("Sensor_right_front_front Undetected\n");

    if (CheckBit(data, 4))
        printf("Sensor_hand_front Detected\n");
    else
        printf("Sensor_hand_front Undetected\n");

    if (CheckBit(data, 2))
        printf("Sensor_left_front_ground Detected\n");
    else
        printf("Sensor_left_front_ground Undetected\n");

    if (CheckBit(data, 1))
        printf("Sensor_left_front_left Detected\n");
    else
        printf("Sensor_left_front_left Undetected\n");

    if (CheckBit(data, 0))
        printf("Sensor_left_front_front Detected\n");
    else
        printf("Sensor_left_front_front Undetected\n");
}

char findCharIdx(char val, char *data_p)
{
    char *ptr = strchr(data_p, val);
    if (ptr == NULL)
        return ERROR;

    return (ptr - data_p);
}