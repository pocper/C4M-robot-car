#include "global_def.h"

#include "USART.h"
#include "USART_protocal.h"
#include "sensor.h"
#include "servo.h"
#include "car.h"

#include "c4mlib/C4MBios/device/src/device.h"

#include <stdio.h>

// TODO
// Movement Master -> Slave RPM = -58 PWM = 0.5 [ms]
// 擴充版範圍為0.85ms -> 2.15 ms

int main()
{
    // MicroUSB通訊初始化
    C4M_STDIO_init();

    // UART0通訊初始化 -> 開啟USART0_RX中斷
    UART0_init();

    // UART1通訊初始化 -> Master/Slave通訊
    UART1_init();

    // 感應器初始化
    sensor_init();

    // 車斗/輪子禁能初始化
    task_init();
    sei();

    // 擴充版Buffer初始化
    Buffer_init();

    //等待擴充版初始化
    _delay_ms(30);

    // 16軸伺服機初始化
    servo_init();

    printf("Start Master\n");

    while (1)
    {
        if (DataLength() > 0)
        {
            // DataDisplay();
            servo_str_split();
            servo_enable_str_split();
            servo_wheel_disable_str_split();
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
