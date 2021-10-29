/**
 * @file common.h
 * @author LiYu87
 * @date 2019.02.22
 * @brief 宣告 C4M_DEVICE_set 原型。
 *
 * @priority 0
 */

#ifndef C4MLIB_DEVICE_DEVICE_H
#define C4MLIB_DEVICE_DEVICE_H


#include "asabus.h"

#include "config_str.h"
#include "isr.h"
#include "bits_op.h"
#include "std_res.h"
#include "stdio.h"

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

/**
 * @defgroup device_func device functions
 */

/* Public Section Start */
/**
 * @brief 進行硬體初始化的動作，包含asabus、stdio初始化。
 * @ingroup device_func
 *
 * 針對不同的硬體平台，將硬體初始化，包含下列動作：
 *   1. STDIO 及硬體初始化：請參照 C4M_STDIO_init。
 *   2. ASABUS ID 硬體初始化：請參照 ASABUS_ID_init。
 *   3. ASABUS SPI 硬體初始化：請參照 ASABUS_SPI_init。
 *   4. ASABUS UART 硬體初始化：請參照 ASABUS_UART_init。
 *   5. EEPROM 初始化及讀取裝置ID。
 *   6. 外掛函式系統的初始化。
 */
void C4M_DEVICE_set(void);
/* Public Section End */

extern AsaConfig_t ASAConfigStr_inst;

#endif  // C4MLIB_DEVICE_DEVICE_H
