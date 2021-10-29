/**
 * @file hal_uart.h
 * @author Ye cheng-Wei
 * @date 2019.1.22
 * @brief Create a hardware abstraction layer to separate hardware dependent.
 */

#ifndef C4MLIB_HARDWARE_HAL_UART_H
#define C4MLIB_HARDWARE_HAL_UART_H

#define DEFAULTUARTBAUD 38400

#include <stdint.h>

/**
 * @defgroup hw_hal_uart_struct hardware hal uart struct
 */

/**
 * @brief uart Master 抽象層結構定義
 *
 * @ingroup hw_struct
 * @ingroup hw_hal_uart_struct
 */
typedef struct {
    void (*init)(void);                         ///< uart初始化函式指標
    void (*tx_compelete_cb)(void);              ///< uart tx call back函式指標
    void (*rx_compelete_cb)(void);              ///< uart rx call back函式指標
    void (*write_byte)(uint8_t data,uint16_t waittick);           ///< uart送出單筆資料函式指標
    void (*write_multi_bytes)(
        uint8_t* data_p, uint8_t sz_data,uint16_t waittick);      ///< uart送出多筆資料函式指標
    void (*read_byte)(uint8_t* data_p,uint16_t waittick);         ///< uart接收單筆資料函式指標
    void (*read_multi_bytes)(uint8_t* data_p, uint8_t sz_data,
                             uint16_t waittick);  ///< uart接收多筆資料函式指標
    uint8_t* error_code;                        ///< 錯誤代碼
} TypeOfUARTInst;

extern TypeOfUARTInst UART0_Inst;
extern TypeOfUARTInst UART1_Inst;

/*
#if defined(__AVR_ATmega128__)
extern TypeOfUARTInst UART0_Inst;
extern TypeOfUARTInst UART1_Inst;
#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || \
    defined(__AVR_ATmega168__)
extern TypeOfUARTInst UART0_Inst;
#elif defined(__AVR_ATtiny2313__)
extern TypeOfUARTInst UART0_Inst;
#else
#    if !defined(__COMPILING_AVR_LIBC__)
#        warning "device type not defined"
#    endif
#endif
*/

#endif  // C4MLIB_HARDWARE_HAL_UART_H
