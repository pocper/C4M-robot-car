#include "pwm_def.h"

#include "c4mlib/C4MBios/macro/src/bits_op.h"
#include "c4mlib/C4MBios/hardware/src/isr.h"

#include <string.h>

#define maxReceieveBuffer 200

#define ENABLE 1
#define DISABLE 0

uint8_t findStr(uint8_t Length, uint8_t start_idx, uint8_t find, void *Data_p);

/**
 * @brief 處理字串中手臂動作函式
 *
 * 格式 : [SERVO_HEADER] [RegAdd] [Data] [SERVO_ENDING]
 * 範例 :      0xB0        0x01    0x9E       0xB0
 * 意義 : Servo 1  轉到 +30度
 *
 * 資料大小
 * Header : uint8_t
 * RegAdd : uint8_t
 * Data   : uint8_t
 * Ending : uint8_t
 *
 * 通道數值(RegAdd)
 * 通道範圍 : 0 ~ 10
 * 代表
 *    -- 0 ~  6 有限角伺服機(手臂/車斗)
 *    -- 7 ~ 10 無限轉伺服機(輪子)
 *
 * 資料範圍(Data)
 * 接收資料 :    0 ~ 255
 * 轉換資料 : -128 ~ 127 [度]
 *
 */
void servo_str_split();

/**
 * @brief 處理字串中PWM通道禁致能函式
 *
 * 格式 : [SERVO_EN_HEADER] [RegAdd] [Data] [SERVO_EN_ENDING]
 * 範例 :       0xB1          0x01    0x01         0xB1
 * 意義 : Servo 1 致能
 *
 * 資料大小
 * Header : uint8_t
 * RegAdd : uint8_t
 * Data   : uint8_t
 * Ending : uint8_t
 *
 * 通道數值(RegAdd)
 * 通道範圍 : 0 ~ 10
 * 代表
 *    -- 0 ~  3 無限轉伺服機(輪子)
 *    -- 4 ~ 10 有限角伺服機(手臂)
 *
 * 資料範圍(Data)
 * 接收範圍 : 0 ~ 1
 * 致能 : 1
 * 禁能 : 0
 */
void servo_enable_str_split();

/**
 * @brief 處理字串中輪子動作函式
 *
 * 格式 : [MOVEMENT_HEADER] [Data] [MOVEMENT_ENDING]
 * 範例 :        0xB2        0x57         0xB2
 * 意義 : Servo 7 ~ 10 向前移動
 *
 * 資料大小
 * Header : uint8_t
 * Data   : uint8_t
 * Ending : uint8_t
 *
 *
 * 資料範圍(Data)
 * 資料範圍 : movement_key中的字元
 * uint8_t movement_key[] = "WASDQEZCR";
 * 轉換資料 : 向前 向左 向後 向右 向左前 向右前 向左後 向右後 順時針轉
 */
void movement_str_split();

/**
 * @brief 清除特定字串函式
 * 格式 : [ERR_HEADER] [Data_1] ... [Data_n] [ERR_HEADER]
 *
 * 清除範圍 : [ERR_HEADER] ~ [ERR_HEADER] 之間
 *
 */
void str_Remove();

/**
 * @brief 接收緩衝區資料顯示函式
 *
 */
void DataDisplay();
