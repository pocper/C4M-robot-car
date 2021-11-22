#include "servo.h"
#include "pwm_def.h"
// Windows

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Linux
#include <unistd.h>

#define FGETS_MAX_LEN 60
#define CSV_LINE_LEN 7
#define ARMDATA_LEN CSV_LINE_LEN - 1

void read_csv(int fd, char *fileName)
{
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL)
        return;

    int ArmData[ARMDATA_LEN];
    uint8_t line_counter = 0;

    char line[FGETS_MAX_LEN];
    char *element = NULL;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        element = strtok(line, ",");
        if (line_counter == 0)
        {
            line_counter++;
            continue;
        }

        // [Index] [loading] [rotate_arm] [1st_arm] [2nd_arm] [3rd_arm] [hand]
        for (int i = 0; i < ARMDATA_LEN; i++)
        {
            // Index
            if (i == 0)
            {
                // int idx = atoi(element);
                continue;
            }

            ArmData[i - 1] = atoi(element);

            element = strtok(NULL, ",");
        }

        arm_trm(fd, ArmData);
        line_counter++;
        usleep(500000);
    }

    fclose(fp);
}

void arm_trm(int fd, int *data_p)
{
    // char sendData[SERVO_POS_ENDING + 1];
    for (int i = 0; i < ARMDATA_LEN; i++)
    {
        dprintf(fd, "%02X%02X%02X%02X", SERVO_HEADER, i, deg2Byte(data_p[i]), SERVO_ENDING);
        // write(fd, sendData, sizeof(sendData));
    }
    // usleep(500000);
}

void MOTION_ENABLE_ALL(int fd)
{
    // dprintf(fd, "%02X%02X%02X%02X", SERVO_EN_HEADER, , SERVO_EN_ENDING);
}
void motion_trm(int fd, char data_p)
{
    // char sendData[SERVO_POS_DATA + 1];
    dprintf(fd, "%02X%c%02X", MOVEMENT_HEADER, data_p, MOVEMENT_HEADER);
    // write(fd, sendData, sizeof(sendData));

    // usleep(500000);
}
int deg2Byte(int num)
{
    return num + 128;
}