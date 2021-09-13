#include "c4mlib.h"
#include <string.h>
#include <stdlib.h>

#define maxReceieveBuffer 100
#define UARTBAUD 38400

/**
 * @brief 初始化USART通訊
 * 
 */
void UART_init();

/**
 * @brief 初始設定Timer0，
 *        目前為處理藍芽接收字串
 * 
 */
void timer0_init();