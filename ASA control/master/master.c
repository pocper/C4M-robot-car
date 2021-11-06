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

// findstr 0xAA || 0xB0系列 介於90~255 之間 findstr 會找到資料

int main()
{
    // MicroUSB通訊初始化
    C4M_STDIO_init();

    // UART0通訊初始化 -> 開啟USART0_RX中斷
    UART0_init();

    // UART1通訊初始化 -> Master/Slave通訊
    UART1_init();

    // sensor_init();

    // 車斗/輪子禁能初始化
    // task_init();
    sei();

    Buffer_init();
    _delay_ms(30); //等待擴充版初始化

    servo_init();

    printf("Start\n");

    while (1)
    {
        if (DataLength() > 0)
        {
            DataDisplay();
            servo_str_split();
            servo_enable_str_split();
            movement_str_split();
            str_Remove();
        }
        else
        {
            _delay_ms(20);
        }
    }

    return 0;
}
