#include "USART.h"
#include "USART_protocal.h"

#include "PCA9685.h"

#include "src/device.h"
#include "src/stdio.h"
#include "src/isr.h"

int main()
{
    C4M_STDIO_init();
    UART0_init();
    PCA9685_init();
    sei();
    // printf("Start Slave\n");

    while (1)
    {
        // DataDisplay();
        handle_rec_str();
        PCA9685_update();
        str_Remove();

        // 用輪詢卡DELAY做50HZ的定週期檢查及輸出更新
        if (DataLength() == 0)
            _delay_ms(20);
    }

    return 0;
}
