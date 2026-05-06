#include "USART.h"
#include "hardware.h"
#include "c4mlib/C4MBios/device/src/device.h"

#include <stdio.h>

// WASD QE G
// WASD 上下左右
// QE 順時針旋轉逆時針
// G 四輪停止

int main()
{
    // MicroUSB通訊初始化
    C4M_STDIO_init();

    // UART0通訊初始化 -> 開啟USART0_RX中斷
    UART0_init();

    // UART1通訊初始化 -> Master/Slave通訊
    UARTM_Inst.init();
    sei();

    //等待擴充版初始化
    _delay_ms(30);

    servo_init();


    while (1)
        ;

    return 0;
}
