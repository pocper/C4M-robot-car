#include <stdint.h>

#define WAITTICK 10

#define ERR_TIMEOUT 255

#define UART0BAUD 38400
#define UART1BAUD 38400

#define DELAY(tick)                  \
    for (int i = 0; i < tick; i++)   \
    {                                \
        __asm__ __volatile__("nop"); \
    }

/**
 * @brief 初始化UART0通訊
 *
 */
void UART0_init();

/**
 * @brief 初始化UART1通訊
 *
 */
void UART1_init();

/**
 * @brief UART0單位元資料傳送函式
 *
 * @param data uint8_t 資料
 */
void UART0_buf_trm(uint8_t data);

/**
 * @brief UART1單位元資料傳送函式
 *
 * @param data uint8_t 資料
 */
void UART1_buf_trm(uint8_t data);

/**
 * @brief UART1資料封包位元組傳送函式
 * // [Header] [RegAdd] [Bytes] [Data_1] ... [Data_Bytes] [End]
 *
 * @param RegAdd          uint8_t  模式
 * @param Bytes           uint8_t  整筆資料大小
 * @param SingleDataSize  uint8_t  單筆資料大小
 * @param Data_p          void*    資料地址
 */
void UART1_trm(uint8_t RegAdd, uint8_t Bytes, uint8_t SingleDataSize, void *Data_p);