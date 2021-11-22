#include <stdint.h>
#ifndef SENSOR_H
#define SENSOR_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief UART特定字串接收函式
 * 
 * @param fd 開啟檔案之描述，fildes
 */
int16_t UART_sensor_rec(int fd);

/**
 * @brief 更新感應器資料函式
 * 
 * @param data uint16_t，感應器資料
 */
void updateSensor(int16_t data);

/**
 * @brief 尋找特定字串函式
 * 
 * @param val 待尋找字串
 * @param data_p 接收字串暫存區陣列地址
 * @return char 待尋找字串之接收字串暫存區索引
 */
uint8_t findCharIdx(uint8_t val, uint8_t *data_p);
#ifdef __cplusplus
}
#endif
#endif