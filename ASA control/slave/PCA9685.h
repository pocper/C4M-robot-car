#include <stdint.h>

/**
 * @brief 對PCA9685晶片初始化函式
 *
 */
void PCA9685_init();

/**
 * @brief 對PCA9685晶片更新PWM函式
 *
 */
void PCA9685_update();

/**
 * @brief 更新陣列數值函式
 *
 * @param RegAdd          uint8_t  模式
 * @param Bytes           uint8_t  整筆資料大小
 * @param SingleDataBytes uint8_t  單筆資料大小
 * @param Data_p          void*    資料地址
 */
void PCA9685_mode(uint8_t RegAdd, uint8_t Bytes, uint8_t SingleDataBytes, void *Data_p);