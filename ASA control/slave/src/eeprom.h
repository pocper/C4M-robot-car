/**
 * @file eeprom.h
 * @author Ye cheng-Wei
 * @date 2019.01.28
 * @brief 宣告 eeprom 操作函式原型。
 */

#ifndef C4MLIB_DEVICE_EEPROM_H
#define C4MLIB_DEVICE_EEPROM_H

/**
 * defgroup eeprom_func
 */

/* Public Section Start */
/**
 * @brief EEPROM設定函式
 *
 * @ingroup eeprom_func
 * @param Address 要寫入的EEPROM位址。
 * @param Bytes   資料大小。
 * @param Data_p  資料指標。
 */
void EEPROM_set(int Address, char Bytes, void *Data_p);

/**
 * @brief EEPROM get 函式
 *
 * @ingroup eeprom_func
 * @param Address 要讀取的EEPROM位址。
 * @param Bytes   資料大小。
 * @param Data_p  資料指標。
 */
void EEPROM_get(int Address, char Bytes, void *Data_p);
/* Public Section End */

#endif  // C4MLIB_DEVICE_EEPROM_H
