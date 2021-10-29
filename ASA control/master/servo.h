#include "USART.h"

#include "pwm_def.h"

#include <avr/interrupt.h>
#include <avr/io.h>

/**
 * @brief 初始化擴充版硬體PWM函式
 *
 */
void servo_init();

/**
 * @brief 設定PWM總開關函式
 * 
 * @param Enable 禁致能參數，1: 致能，0:禁能
 */
void servo_Power(uint8_t Enable);

/**
 * @brief 設定PWM通道致能調整函式
 *
 * @param channel 設定通道0~11
 * 0 ~  6為手臂伺服機
 * 7 ~ 10為輪子伺服機
 * @param Enable 禁致能參數，1: 致能，0:禁能
 */
void servo_Enable(uint8_t channel, uint8_t Enable);

/**
 * @brief 更新PWM單一通道函式
 *
 * @param channel 設定通道0~10
 *  - 0 ~  6為手臂伺服機
 *  - 7 ~ 10為輪子伺服機
 * @param val 數值參數(0~6通道為角度[Deg]，7~10為轉速[RPM])
 * @return uint8_t 錯誤代碼：
 */
uint8_t servo_update(uint8_t channel, float val);

/**
 * @brief PWM轉換為擴充版晶片數值函式
 *  - 0.50 [ms] ->   0 等份。
 *  - 2.50 [ms] -> 410 等份。
 * @param PWM 波寬調變數值
 * @return uint16_t 錯誤代碼：
 */
uint16_t PWM2Tick(float PWM);

/**
 * @brief 角度轉換為PWM數值函式
 *  -112.5 [Deg] -> 0.5 [ms]。
    +112.5 [Deg] -> 2.5 [ms]。
 *
 * @param Degree 角度，單位[Deg]
 * @return float PWM，單位[ms]
 */
float Deg2PWM(int8_t Degree);

/**
 * @brief RPM轉換為PWM數值函式
 *
 * @param RPM 轉速，單位[rpm]
 * @return uint8_t PWM，單位[ms]
 */
uint8_t RPM2PWM(int8_t RPM);