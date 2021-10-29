/**
 * @file device.c
 * @author LiYu87
 * @date 2019.10.13
 * @brief 實現C4M_DEVICE_set以及宣告所需全域變數。
 */


#include "asabus.h"
#include "config_str.h"
//#include "eeprom.h"
#include "stdio.h"


void C4M_DEVICE_set(void);

/* Global variables section ------------------------------------------------- */

AsaConfig_t ASAConfigStr_inst;

void C4M_DEVICE_set(void) {
    C4M_STDIO_init();
    ASABUS_ID_init();
    
    // 從EEPROM中讀取裝置ID，並放入結構ASAConfigStr_inst中
    // 預設裝置ID為0
//    EEPROM_get(0, sizeof(ASAConfigStr_inst), &ASAConfigStr_inst);

}
