#include "global_def.h"

#include "USART.h"
#include "USART_protocal.h"
#include "sensor.h"
#include "servo.h"
#include "car.h"

#include "c4mlib/C4MBios/device/src/device.h"

#include <stdio.h>

// TODO
// Movement Master -> Slave RPM = -58 PWM =0.5 [ms]
// 擴充版範圍為0.85ms -> 2.15 ms

//  手臂初始化位置
//  1) 將手臂歸位置特定位置
//  2) 先伸展到不會撞到任何牆壁
//  3) 再伸到比賽要求位置

// 看要不要把Include 合併進car.h
// slave端程式化簡

int main()
{
    C4M_STDIO_init();
    UART0_init();
    // sensor_init();
    task_init();
    servo_init();
    sei();

    _delay_ms(100); //等待擴充版初始化
    printf("Start\n");
    servo_Power(ENABLE);
    servo_Enable(0, ENABLE);

    while (1)
    {
        // DataDisplay();
        servo_str_split();
        servo_enable_str_split();
        movement_str_split();
        str_Remove();

        if (DataLength() == 0)
            _delay_ms(20);
    }

    return 0;
}
