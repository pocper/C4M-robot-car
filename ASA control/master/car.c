#include "global_def.h"

#include "car.h"
#include "timer.h"
#include "servo.h"
#include "USART_protocal.h"

#include "c4mlib/C4MBios/hardware/src/isr.h"

#include <stdio.h>

Task task;
Wheel wheelVal = {-1, 1, -1, 1};
uint8_t RPM = 58;

ISR(TIMER1_COMPA_vect)
{
    for (int task_num = 0; task_num < TotalTask; task_num++)
    {
        if (task.Counter[task_num] == task.Target[task_num])
        {
            //車斗禁能
            if (task_num == 0)
            {
                servo_enable_str_concat(0, DISABLE);
                servo_enable_str_concat(1, DISABLE);
            }

            //輪子禁能
            if (task_num == 1)
            {
                servo_enable_str_concat(7, DISABLE);
                servo_enable_str_concat(8, DISABLE);
                servo_enable_str_concat(9, DISABLE);
                servo_enable_str_concat(10, DISABLE);
            }
        }

        if (task.Counter[task_num] <= task.Target[task_num])
            task.Counter[task_num]++;
    }
}

void task_init()
{
    //時間：200.00 [ms]
    timer1_init();

    // 車斗
    //待測 - 經過時間
    //估計時間 : 0.528399 [s]
    task.Target[0] = 1;
    task.Counter[0] = task.Target[0] + 1; //初始化

    // 車輪
    //待測 - 經過時間
    //估計時間 : 0.528399 [s]
    task.Target[1] = 1;
    task.Counter[1] = task.Target[1] + 1; //初始化
}

void Movement_condition(uint8_t Dir)
{
    // printf("Dir =%d\n", Dir);

    switch (Dir)
    {
    case forward:
        wheelVal.left_front = -1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = 1;
        break;

    case backward:
        wheelVal.left_front = 1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = -1;
        break;

    case left:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;

    case right:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;

    case right_front:
        wheelVal.left_front = -1;
        wheelVal.right_front = 0;
        wheelVal.left_rear = 0;
        wheelVal.right_rear = 1;
        break;

    case left_front:
        wheelVal.left_front = 0;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = 0;
        break;

    case right_behind:
        wheelVal.left_front = 1;
        wheelVal.right_front = 0;
        wheelVal.left_rear = 0;
        wheelVal.right_rear = -1;
        break;

    case left_behind:
        wheelVal.left_front = 0;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 0;
        break;

    case rotate_cw:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;

    case rotate_ccw:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;
    }

    Movement_update();
}

void Movement_update()
{
    /*
            ---front---
            ___________
    9 -     |         |   - 7
            |         |
            |         |
            |         |
            |         |   - 8
    10 -    |_________|
            ---back---
    */

    servo_update(7, RPM * wheelVal.right_front);
    servo_update(8, RPM * wheelVal.right_rear);
    servo_update(9, RPM * wheelVal.left_rear);
    servo_update(10, RPM * wheelVal.left_front);

    task.Counter[1] = 0;
}

void Rotation_update(uint8_t channel, int8_t Degree)
{
    // printf("channel = %d val = %d\n", channel, Degree);

    if (channel == 0 || channel == 1)
    {
        servo_update(0, Degree);
        servo_update(1, Degree);

        task.Counter[0] = 0;
    }
    else if (channel == 3)
    {
        servo_update(3, Degree);
        servo_update(11, Degree);
    }
    else if (channel == 4)
    {
        servo_update(4, Degree);
        servo_update(12, Degree);
    }
    else
    {
        // servo_update(channel, Degree);
        interpolation(channel, Degree);
    }
}

void interpolation(uint8_t channel, int8_t dest_Degree)
{
    static int8_t begin_Degree[7];
    static uint8_t isFirstRotate = 0x7f;

    if (CheckBit(isFirstRotate, channel))
    {
        servo_update(channel, dest_Degree);
        begin_Degree[channel] = dest_Degree;
        BIT_CLEAR(isFirstRotate, channel);
    }
    else
    {
        int8_t delta = dest_Degree - begin_Degree[channel];
        uint8_t abs_delta = delta > 0 ? delta : -delta;
        uint8_t total_split;

        if (abs_delta > 45)
            total_split = abs_delta / 15;
        else
            total_split = 1;

        if (total_split == 1)
        {
            servo_update(channel, dest_Degree);
        }
        else
        {
            for (int split = 0; split < total_split; split++)
            {
                servo_update(channel, begin_Degree[channel] + (float)(delta) * (split + 1) / total_split);
            }
        }

        begin_Degree[channel] = dest_Degree;
    }
}