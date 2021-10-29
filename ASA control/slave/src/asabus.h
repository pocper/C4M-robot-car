/**
 * @file asabus.h
 * @author LiYu87
 * @brief asabus 相關硬體操作函式原型。
 * @date 2019.10.13
 */

#ifndef C4MLIB_ASABUS_H
#define C4MLIB_ASABUS_H

#include "hal_spi.h"
#include "hal_uart.h"

#define UARTM_Inst (UART1_Inst)
#define UARTS_Inst (UART1_Inst)
#define SPIM_Inst (SPI_MasterInst)
#define SPIS_Inst (SPI_SlaveInst)

/*
#if defined(__AVR_ATmega128__)
#    define UARTM_Inst (UART1_Inst)
#    define UARTS_Inst (UART1_Inst)
#    define SPIM_Inst (SPI_MasterInst)
#    define SPIS_Inst (SPI_SlaveInst)
#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || \
    defined(__AVR_ATmega168__)
#    define UARTS_Inst (UART_Inst)
#elif defined(__AVR_ATtiny2313__)
#    define UARTS_Inst (UART_Inst)
#else
#    if !defined(__COMPILING_AVR_LIBC__)
#        warning "device type not defined"
#    endif
#endif
*/

/**
 * @defgroup asabus_func asabus functions
 * @defgroup asabus_macro asabus macros
 */

/* Public Section Start */
/**
 * @brief 初始化ASABUS上的ID腳位。
 * @ingroup asabus_func
 *
 * ASABUS 上的 ID 腳位共有三隻，分別為ADDR0、ADDR1、ADDR2。
 * 呼叫此函式將會對前述三隻腳位進行初始化，設定為輸出。
 *
 * 以下是常見的板子上的ADDR腳位
 * asam128_v2:
 *  - ADDR0 : PF5
 *  - ADDR1 : PF6
 *  - ADDR2 : PF7
 *
 * 注意：在呼叫 C4M_DEVIDE_set 的時候也會執行此函式。
 */
void ASABUS_ID_init(void);

/**
 * @brief 設定ASABUS上使用的ID，0~7。
 * @ingroup asabus_func
 *
 * @param id 要設定的 ID 編號，0~7。
 *
 * 可以設定的ID為0~7，轉換成2進位每個bit分別對應到 ADDR0、ADDR1、ADDR2。
 * 若該bit被設定為1，則會令對應腳位輸出 1(logic high)。如果傳入 id
 * 編號非0~7，則不會進行設定的動作。
 *
 * 以下是常見的板子上的ADDR腳位<br>
 *  - asam128_v2:
 *    - ADDR0 : PF5
 *    - ADDR1 : PF6
 *    - ADDR2 : PF7
 */
void ASABUS_ID_set(char id);

/**
 * @brief 初始化ASABUS上的UART硬體。
 * @ingroup asabus_func
 *
 * 針對 ASABUS 上所使用的 UART 硬體進行初始化，會設定鮑率為38400、
 * 停止位元為1、傳輸大小為8位元。
 *
 * 注意：在呼叫 C4M_DEVIDE_set 的時候也會執行此函式。
 * 
 * 以下是常見的板子使用的uart硬體編號：<br>
 *  - asam128_v2: uart0
 */
void ASABUS_UART_init(void);

/**
 * @brief 將資料透過 ASABUS UART 傳送。
 * @ingroup asabus_func
 *
 * 等待並接收 ASABUS UART 來的資料，沒有逾時機制，
 * 所以若硬體錯誤將不會離開此函式。
 */
void ASABUS_UART_transmit(char data);

/**
 * @brief 等待並接收 ASABUS UART 來的資料。
 * @ingroup asabus_func
 *
 * @return char 接收回來的資料。
 *
 * 沒有逾時機制，所以若硬體錯誤將不會離開此函式。
 * 所以若硬體錯誤將不會離開此函式。
 */
char ASABUS_UART_receive(void);

/**
 * @brief 初始化ASABUS上的SPI硬體。
 * @ingroup asabus_func
 *
 * 針對 ASABUS 上所使用的 SPI 硬體進行初始化，設定為master模式，
 * SCK頻率則會因硬體而異。
 *
 * 注意：在呼叫 C4M_DEVIDE_set 的時候也會執行此函式。
 *
 * 以下是常見的板子使用的spi及初始化參數：<br>
 *  - asam128_v2: spi
 *    - SCK 頻率: fosc/64 = 11059200/64 = 172.8 kHz。
 *    - CPOL = 0，前緣為上升緣。
 *    - CPHA = 0，取樣時間為前緣。
 */
void ASABUS_SPI_init(void);

/**
 * @brief 與 ASABUS SPI 交換資料。
 * @ingroup asabus_func
 *
 * @param data 要交換的資料。
 * @return char 交換回來的資料。
 *
 * 沒有逾時機制，所以若硬體錯誤將不會離開此函式。
 * 
 * 以下是常見的板子使用的uart硬體編號：<br>
 *  - asam128_v2: spi
 */
char ASABUS_SPI_swap(char data);
/* Public Section End */

#endif  // C4MLIB_ASABUS_H
