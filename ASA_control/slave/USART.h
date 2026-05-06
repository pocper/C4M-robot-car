#include <stdint.h>

#define UART0BAUD 38400

/**
 * @brief 初始化UART0通訊
 *
 */
void UART0_init();

/**
 * @brief UART0單位元資料傳送函式
 *
 * @param data uint8_t 資料
 */
void UART0_buf_trm(uint8_t data);