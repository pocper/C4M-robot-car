#include "c4mlib/C4MBios/device/src/device.h"

#include "USART_protocal.h"
#include "sensor.h"
#include "servo.h"
#include "car.h"

#include <stdio.h>

// TODO
// Interpolation 原切分100等份
// 改為越小角度切分越小 -> 最小一次1度

// 降低Master -> Slave 的資料長度
// 原為16通道資料一起送
// 改為單一通道送
// 輪子的話一次四顆更新

int main()
{
    C4M_STDIO_init();
    UART0_init();
    sensor_init();
    task_init();
    // servo_init();
    _delay_ms(100); //等待擴充版初始化
    sei();

    // printf("Start\n");

    while (1)
    {
        // DataDisplay();
        servo_str_split();
        servo_enable_str_split();
        movement_str_split();
        str_Remove();
        _delay_ms(50);
    }

    return 0;
}
