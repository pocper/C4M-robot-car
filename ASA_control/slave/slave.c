#include "USART.h"
#include "hardware.h"
#include "src/isr.h"

#include <util/delay.h>

// 電流保護上限值 ->需做怎樣的動作才算正常，怎樣算不正常
// 過電保護 -> 可以檢查超過門檻時間，過久才停掉
// 過電保護 -> 離電池過電保護後就不會開啟了
// 用電供測試看看 8.4V 電流用電供測試看看
int main()
{
    PowerRelay_init();

    UART0_init();

    RegAdd_init();
    // EEPROM_read();
    tmp_EEPROM_read();

    PCA9685_init();
    // ADG794_init();
    // DCPlugInDetect_init();
    sei();

    PowerRelay_update();
    _delay_ms(100);

    while (1)
    {
        // EEPROM_update();
        PowerRelay_update();
        PCA9685_update();
        // DCPlugInDetect_update();
        // ADC_update();
        // CurrentProtect_update();

        // 用輪詢卡DELAY做50HZ的定週期檢查及輸出更新
        _delay_ms(20);
    }
    return 0;
}
