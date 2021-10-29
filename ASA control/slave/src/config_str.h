/**
 * @file config_str.h
 * @author Ye Chen-Wei
 * @date 2019.01.28
 * @brief Provide ASA non-volatile configuration structure
 */

#ifndef C4MLIB_DEVICE_CONFIG_STR_H
#define C4MLIB_DEVICE_CONFIG_STR_H

#include <stdint.h>
/**
 * @brief 開發版資訊管理結構。
 *
 * 在對硬體初始化(C4M_DEVICE_set)時，會讀取EEPROM內的內容，
 * 並放入 ASAConfigStr_inst 中。
 */
typedef struct {
    uint8_t ASA_ID;  ///< 裝置所對應的ID
} AsaConfig_t;

#endif  // C4MLIB_DEVICE_CONFIG_STR_H
