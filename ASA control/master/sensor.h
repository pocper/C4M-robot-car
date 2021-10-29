
#include "pwm_def.h"
#include "USART.h"
#include "timer.h"

#include "c4mlib/C4MBios/macro/src/bits_op.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"

#include <avr/io.h>

/**
 * @brief 初始化感應器暫存器，
 *  目前使用
 *  - SensorA
 *  - SensorB
//  *  - SensorC -> error atmega128 PE7 cannot be input I/O
 *  - SensorD
 *  - SensorE
 *  - SensorF
 *
 */
void sensor_init();

/**
 * @brief 初始化感應器A之暫存器
 *
 */
void sensorA_init();

/**
 * @brief 初始化感應器B之暫存器
 *
 */
void sensorB_init();

/**
 * @brief 初始化感應器C之暫存器
 *
 */
void sensorC_init();

/**
 * @brief 初始化感應器D之暫存器
 *
 */
void sensorD_init();

/**
 * @brief 初始化感應器E之暫存器
 *
 */
void sensorE_init();

/**
 * @brief 初始化感應器F之暫存器
 *
 */
void sensorF_init();

/**
 * @brief 資料彙整函式，
 * 將五個感應器資料彙整成 uint16_t
 *
 *
 * @return uint16_t 感應器資料
 * [Header] [SensorA1] [SensorA2] [SensorA3] ... [SensorF1] [SensorF2] [SensorF3] [Ending]
 * 
 */
uint16_t sensor_rec();