#include <stdio.h>

/**
 * @brief UART特定字串接收函式
 * 
 * @param fd 開啟檔案之描述，fildes
 */
void UART_sensor_rec(int fd);


/**
 * @brief 更新感應器資料函式
 * 
 * @param data uint16_t，感應器資料
 */
void updateSensor(int data);

/**
 * @brief 尋找特定字串函式
 * 
 * @param val 待尋找字串
 * @param data_p 接收字串暫存區陣列地址
 * @return char 待尋找字串之接收字串暫存區索引
 */
char findCharIdx(char val, char *data_p);