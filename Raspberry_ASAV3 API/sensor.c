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

    // Test Receive Data
    for (int i = 0; i < bytes_num; i++)
        fprintf(STDOUT_FILENO,"%c", receiveBuffer[i]);
    fprintf(STDOUT_FILENO,"\n");
    

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
        fprintf(STDOUT_FILENO,"Sensor_right_behind_ground Detected");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_behind_ground\n");

    if (CheckBit(data, 13))
        fprintf(STDOUT_FILENO,"Sensor_right_behind_right Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_behind_right Undetected\n");

    if (CheckBit(data, 12))
        fprintf(STDOUT_FILENO,"Sensor_right_behind_behind Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_behind_behind Undetected\n");

    if (CheckBit(data, 11))
        fprintf(STDOUT_FILENO,"Sensor_left_behind_ground Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_behind_ground Undetected\n");

    if (CheckBit(data, 10))
        fprintf(STDOUT_FILENO,"Sensor_left_behind_left Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_behind_left Undetected\n");

    if (CheckBit(data, 9))
        fprintf(STDOUT_FILENO,"Sensor_left_behind_behind Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_behind_behind Undetected\n");

    if (CheckBit(data, 8))
        fprintf(STDOUT_FILENO,"Sensor_right_front_ground Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_front_ground Undetected\n");

    if (CheckBit(data, 7))
        fprintf(STDOUT_FILENO,"Sensor_right_front_right Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_front_right Undetected\n");

    if (CheckBit(data, 6))
        fprintf(STDOUT_FILENO,"Sensor_right_front_front Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_right_front_front Undetected\n");

    if (CheckBit(data, 4))
        fprintf(STDOUT_FILENO,"Sensor_hand_front Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_hand_front Undetected\n");

    if (CheckBit(data, 2))
        fprintf(STDOUT_FILENO,"Sensor_left_front_ground Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_front_ground Undetected\n");

    if (CheckBit(data, 1))
        fprintf(STDOUT_FILENO,"Sensor_left_front_left Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_front_left Undetected\n");

    if (CheckBit(data, 0))
        fprintf(STDOUT_FILENO,"Sensor_left_front_front Detected\n");
    else
        fprintf(STDOUT_FILENO,"Sensor_left_front_front Undetected\n");
}

char findCharIdx(char val, char *data_p)
{
    char *ptr = strchr(data_p, val);
    if (ptr == NULL)
        return ERROR;

    return (ptr - data_p);
}