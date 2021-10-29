#include "car.h"
#include "timer.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"

Task task;
Wheel wheelVal = {-1, 1, -1, 1};
int RPM = 58;

ISR(TIMER0_COMP_vect)
{
    for (int task_num = 0; task_num < TotalTask; task_num++)
    {
        if (task.Counter[task_num] < task.Target[task_num] + 1)
        {
            task.Counter[task_num]++;
        }

        if (task.Counter[task_num] == task.Target[task_num])
        {
            //車斗禁能
            if (task_num == 0)
            {
                for (int servo_num = 0; servo_num < 2; task_num++)
                    servo_Enable(servo_num, DISABLE);
            }

            //輪子禁能
            if (task_num == 1)
            {
                for (int servo_num = 7; servo_num < 11; task_num++)
                    servo_Enable(servo_num, DISABLE);
            }
        }
    }
}

void task_init()
{
    // 時間： 0.05 [s]
    timer0_init();

    // 車輪
    task.Target[0] = 20;
    task.Counter[0] = task.Target[0] + 1; //初始化

    // 車斗
    // 持續時間
    // S1 -> 574.335 [ms]
    // S2 -> 396.543 [ms]

    // 啟動相差時間
    // S1 Then S2 -> 256.812 [ms]

    task.Target[1] = 20;
    task.Counter[1] = task.Target[1] + 1; //初始化
}

void Movement_condition(int Dir)
{
    printf("Dir =%d\n", Dir);

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
    printf("channel = %d val = %d\n", channel, Degree);

    if (channel == 0 || channel == 1)
    {
        //- 3 degree is the best horizontal set
        //-60 degree is vertical set
        servo_update(0, Degree);
        servo_update(1, Degree);

        task.Counter[0] = 0;
    }
    else
    {
        servo_update(channel, Degree);
        // interpolation(channel, Degree);
    }
}

void interpolation(uint8_t channel, int8_t dest_Degree)
{
    static int begin_Degree[7];
    static char isFirstRotate[7] = {1, 1, 1, 1, 1, 1, 1};

    if (isFirstRotate[channel])
    {
        servo_update(channel, dest_Degree);
        begin_Degree[channel] = dest_Degree;
        isFirstRotate[channel] = 0;
    }
    else
    {
        float temp_Degree;

        for (int split = 0; split < interpolation_split; split++)
        {
            temp_Degree = (float)(split * (dest_Degree - begin_Degree[channel])) / interpolation_split;
            servo_update(channel, temp_Degree);
        }

        begin_Degree[channel] = dest_Degree;
    }
}