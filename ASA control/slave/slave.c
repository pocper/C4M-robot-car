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
    printf("Start Slave\n");

    while (1)
    {
        if (DataLength() > 0)
        {
            // DataDisplay();
            handle_rec_str();
            PCA9685_update();
            str_Remove();
        }
        else
        {
            _delay_ms(10);
        }
    }

    return 0;
}
