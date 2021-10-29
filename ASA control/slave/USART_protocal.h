#include "src/bits_op.h"
#include "pwm_def.h"

#include "src/isr.h"
#include <stdlib.h>
#include <string.h>

#define maxReceieveBuffer 200

#define ENABLE 1
#define DISABLE 0

uint8_t findStr(uint8_t Length, uint8_t start_idx, uint8_t find, void *Data_p);

/**
 * @brief 接收緩衝區資料顯示函式
 *
 */
void DataDisplay();

/**
 * @brief 處理receiveData buffer函式
 *
 */
void handle_rec_str();

/**
 * @brief 清除特定字串函式
 * 格式 : [ERR_HEADER] [Data_1] ... [Data_n] [ERR_HEADER]
 *
 * 清除範圍 : [ERR_HEADER] ~ [ERR_HEADER] 之間
 *
 */
void str_Remove();