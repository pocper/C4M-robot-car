#include <stdint.h>

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

/**
 * @brief 返回接收暫存區長度函式
 *
 * @return uint8_t receiveDataLength
 */
uint8_t DataLength();