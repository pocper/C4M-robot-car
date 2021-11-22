#include "sensor.h"
#include "pwm_def.h"
#include "global_def.h"

// Windows
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

// Linux
#include <sys/unistd.h>

#define ERROR 255

int16_t UART_sensor_rec(int fd)
{
    uint8_t receiveBuffer[50];
    char bytes_num = read(fd, &receiveBuffer, sizeof(receiveBuffer));

    // Test Receive Data
    // for (int i = 0; i < bytes_num; i++)
    //     fprintf(stdout, "%c", receiveBuffer[i]);
    // fprintf(stdout, "\n");

    uint8_t sensor_sentence_startIdx = findCharIdx(SENSOR_HEADER, receiveBuffer);

    if (sensor_sentence_startIdx == ERROR)
        return -1;

    uint8_t sensor_sentence_endIdx = findCharIdx(SENSOR_ENDING, receiveBuffer);
    if (sensor_sentence_endIdx == ERROR)
        return -1;

    //[SENSOR_HEADER][Data_H][Data_L][SENSOR_ENDING]
    //       F3         01      01          F4

    int16_t sensorData = 0;
    if ((sensor_sentence_endIdx - sensor_sentence_startIdx) == 4)
    {
        sensorData = receiveBuffer[sensor_sentence_startIdx] << 8;
        sensorData += receiveBuffer[sensor_sentence_startIdx + 1];
    }
    return sensorData;
}

void updateSensor(int16_t data)
{
    if (CheckBit(data, 14))
        fprintf(stdout, "Sensor_right_behind_ground Detected");
    // else
    //     fprintf(stdout, "Sensor_right_behind_ground\n");

    if (CheckBit(data, 13))
        fprintf(stdout, "Sensor_right_behind_right Detected\n");
    // else
    //     fprintf(stdout, "Sensor_right_behind_right Undetected\n");

    if (CheckBit(data, 12))
        fprintf(stdout, "Sensor_right_behind_behind Detected\n");
    // else
    //     fprintf(stdout, "Sensor_right_behind_behind Undetected\n");

    if (CheckBit(data, 11))
        fprintf(stdout, "Sensor_left_behind_ground Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_behind_ground Undetected\n");

    if (CheckBit(data, 10))
        fprintf(stdout, "Sensor_left_behind_left Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_behind_left Undetected\n");

    if (CheckBit(data, 9))
        fprintf(stdout, "Sensor_left_behind_behind Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_behind_behind Undetected\n");

    if (CheckBit(data, 8))
        fprintf(stdout, "Sensor_right_front_ground Detected\n");
    // else
    //     fprintf(stdout, "Sensor_right_front_ground Undetected\n");

    if (CheckBit(data, 7))
        fprintf(stdout, "Sensor_right_front_right Detected\n");
    // else
    //     fprintf(stdout, "Sensor_right_front_right Undetected\n");

    if (CheckBit(data, 6))
        fprintf(stdout, "Sensor_right_front_front Detected\n");
    // else
    //     fprintf(stdout, "Sensor_right_front_front Undetected\n");

    if (CheckBit(data, 4))
        fprintf(stdout, "Sensor_hand_front Detected\n");
    // else
    //     fprintf(stdout, "Sensor_hand_front Undetected\n");

    if (CheckBit(data, 2))
        fprintf(stdout, "Sensor_left_front_ground Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_front_ground Undetected\n");

    if (CheckBit(data, 1))
        fprintf(stdout, "Sensor_left_front_left Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_front_left Undetected\n");

    if (CheckBit(data, 0))
        fprintf(stdout, "Sensor_left_front_front Detected\n");
    // else
    //     fprintf(stdout, "Sensor_left_front_front Undetected\n");
}

uint8_t findCharIdx(uint8_t val, uint8_t *data_p)
{
    uint8_t *ptr = strchr(data_p, val);
    if (ptr == NULL)
        return ERROR;

    return (ptr - data_p);
}