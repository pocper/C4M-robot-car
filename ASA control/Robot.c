#include "Robot.h"

#ifndef _SERVO_H
#define _SERVO_H
#include "servo.h"
#endif

Wheel wheelVal = {-1, 1, -1, 1};
int RPM = 58;

extern Task task;

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
    3 -     |         |   - 1
            |         |
            |         |
            |         |
            |         |   - 2
    4 -     |_________|
            ---back---
    */

    Servo_Speed_set(4, RPM * wheelVal.right_front);
    Servo_Speed_set(5, RPM * wheelVal.right_rear);
    Servo_Speed_set(6, RPM * wheelVal.left_rear);
    Servo_Speed_set(7, RPM * wheelVal.left_front);

    task.counter[0] = 0;
}

uint8_t Rotation_update(uint8_t channel, int8_t Degree)
{
    printf("channel = %d val = %d\n", channel, Degree);

    if (channel < 1 || channel > 7)
        return 255;

    if (Degree > 90 || Degree < -90)
        return 254;

    if (channel == 1 || channel == 2)
    {
        //- 3 degree is the best horizontal set
        //-60 degree is vertical set
        Servo_Degree_set(1, Degree);
        Servo_Degree_set(2, Degree);

        task.counter[1] = 0;
    }
    else
    {
        Servo_Degree_set(channel, Degree);
        // task.counter[2] = 0;
    }

    return 0;
}