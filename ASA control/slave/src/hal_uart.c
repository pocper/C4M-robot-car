/**
 * @file hal_uart.h
 * @author Ye cheng-Wei
 * @date 2019.10.07
 * @brief Implement a hardware abstraction layer for atmega128.
 */

#include "hal_uart.h"

#include "isr.h"
#include "std_res.h"
#include "hal_time.h"
#include "debug.h"

#include <avr/io.h>
#include <stddef.h>
#define UART_DELAY(tick)             \
    for (int i = 0; i < tick; i++)   \
    {                                \
        __asm__ __volatile__("nop"); \
    }
/**
 * @defgroup hw_hal_uart_func hardware hal uart functions
 */

/**
 * @brief M128 UART0 初始化函式。
 *
 * @ingroup hw_hal_uart_func
 */
static void M128_UART0_init();

/**
 * @brief M128 UART0 單筆資料寫入函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data  欲寫入資料。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART0_write_byte(uint8_t data, uint16_t waittick);

/**
 * @brief M128 UART0 多筆資料寫入函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲寫入資料指標。
 * @param sz_data  欲寫入大小。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART0_write_multi_bytes(uint8_t *data_p, uint8_t sz_data, uint16_t waittick);

/**
 * @brief M128 UART0 單筆資料接收函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲接收資料指標。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART0_read_byte(uint8_t *data_p, uint16_t waittick);

/**
 * @brief M128 UART0 多筆資料寫入函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲接收資料指標。
 * @param sz_data  欲接收資料大小。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART0_read_bytes(uint8_t *data_p, uint8_t sz_data,
                                  uint16_t waittick);

/**
 * @brief M128 UART1 初始化函式。
 *
 * @ingroup hw_hal_uart_func
 */
static void M128_UART1_init();

/**
 * @brief M128 UART1 單筆資料寫入函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data  欲寫入資料。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART1_write_byte(uint8_t data, uint16_t waittick);

/**
 * @brief M128 UART1 多筆資料寫入函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲寫入資料指標。
 * @param sz_data  欲寫入大小。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART1_write_multi_bytes(uint8_t *data_p, uint8_t sz_data,
                                         uint16_t waittick);

/**
 * @brief M128 UART1 單筆資料讀取函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲接收資料指標。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART1_read_byte(uint8_t *data_p, uint16_t waittick);

/**
 * @brief M128 UART1 多筆資料讀取函式。
 *
 * @ingroup hw_hal_uart_func
 * @param data_p  欲接收資料指標。
 * @param sz_data  欲接收資料大小。
 * @param waittick 位元組間延遲時間，單位為 1us。
 */
static void M128_UART1_read_bytes(uint8_t *data_p, uint8_t sz_data,
                                  uint16_t waittick);

/**
 * @brief M128 UART0 錯誤代碼
 */
static uint8_t UART0_error_code;

/**
 * @brief M128 UART1 錯誤代碼
 */
static uint8_t UART1_error_code;

TypeOfUARTInst UART0_Inst = {.init = M128_UART0_init,
                             .tx_compelete_cb = 0,
                             .rx_compelete_cb = 0,
                             .write_byte = M128_UART0_write_byte,
                             .write_multi_bytes = M128_UART0_write_multi_bytes,
                             .read_byte = M128_UART0_read_byte,
                             .read_multi_bytes = M128_UART0_read_bytes,
                             .error_code = &UART0_error_code};

TypeOfUARTInst UART1_Inst = {.init = M128_UART1_init,
                             .tx_compelete_cb = 0,
                             .rx_compelete_cb = 0,
                             .write_byte = M128_UART1_write_byte,
                             .write_multi_bytes = M128_UART1_write_multi_bytes,
                             .read_byte = M128_UART1_read_byte,
                             .read_multi_bytes = M128_UART1_read_bytes,
                             .error_code = &UART1_error_code};

void M128_UART0_init()
{
    // Initialize the UART0 with 38400 Baudrate
    uint16_t baud = F_CPU / 16 / DEFAULTUARTBAUD - 1;
    UBRR0H = (unsigned char)(baud >> 8);
    UBRR0L = (unsigned char)baud;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (3 << UCSZ00);

    // Enable RX & TX interrupt
    UCSR0B |= (1 << RXCIE0) | (1 << TXCIE0);
}

void M128_UART0_write_byte(uint8_t data, uint16_t waittick)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ; // Wait for UDR empty
    UDR0 = data;
    UART0_error_code = 0;
    UART_DELAY(waittick);
    return;
}

void M128_UART0_write_multi_bytes(uint8_t *data_p, uint8_t sz_data,
                                  uint16_t waittick)
{
    for (int i = 0; i < sz_data; i++)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ; // Wait for UDR empty
        UDR0 = data_p[i];
        UART_DELAY(waittick);
    }
    UART0_error_code = 0;
    return;
}

void M128_UART0_read_byte(uint8_t *data_p, uint16_t waittick)
{
    HAL_Time expire_time;
    HAL_get_expired_time_ms(50UL,
                            &expire_time); // Get current time tick (Unit: 1ms)
    while (
        !(UCSR0A & (1 << RXC0))) // If there is no RX complete flag, Block here
    {
        if (HAL_timeout_test(expire_time))
        { // Check timeout

            UART0_error_code = HAL_ERROR_TIMEOUT;
            data_p[0] = 0;
            return;
        }
    }
    data_p[0] = UDR0;
    UART0_error_code = 0;
    UART_DELAY(waittick);
    return;
}

void M128_UART0_read_bytes(uint8_t *data_p, uint8_t sz_data,
                           uint16_t waittick)
{
    HAL_Time expire_time;
    for (int i = 0; i < sz_data; i++)
    {
        HAL_get_expired_time_ms(
            50UL, &expire_time); // Get current time tick (Unit: 1ms)

        while (!(UCSR0A &
                 (1 << RXC0))) // If there is no RX complete flag, Block here
        {
            if (HAL_timeout_test(expire_time))
            { // Check timeout

                UART0_error_code = HAL_ERROR_TIMEOUT;
                data_p[i] = 0;
                return;
            }
        }
        data_p[i] = UDR0;
        UART_DELAY(waittick);
    }
    UART0_error_code = 0;
    return;
}

void M128_UART1_init()
{
    // Initialize the UART1 with 38400 Baudrate
    uint16_t baud = F_CPU / 16 / DEFAULTUARTBAUD - 1;
    UBRR1H = (unsigned char)(baud >> 8);
    UBRR1L = (unsigned char)baud;

    UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
    UCSR1C |= (3 << UCSZ10);

    // Enable RX & TX interrupt
    UCSR1B |= (1 << RXCIE1) | (1 << TXCIE1);
}

void M128_UART1_write_byte(uint8_t data, uint16_t waittick)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ; // Wait for UDR empty
    UDR1 = data;
    UART1_error_code = 0;
    UART_DELAY(waittick);
}

void M128_UART1_write_multi_bytes(uint8_t *data_p, uint8_t sz_data,
                                  uint16_t waittick)
{
    for (int i = 0; i < sz_data; i++)
    {
        while (!(UCSR1A & (1 << UDRE1)))
            ; // Wait for UDR empty
        UDR1 = data_p[i];
        UART_DELAY(waittick);
    }
    UART1_error_code = 0;
}

void M128_UART1_read_byte(uint8_t *data_p, uint16_t waittick)
{
    HAL_Time expire_time;
    HAL_get_expired_time_ms(50UL,
                            &expire_time); // Get current time tick (Unit: 1ms)
    while (
        !(UCSR1A & (1 << RXC1))) // If there is no RX complete flag, Block here
    {
        if (HAL_timeout_test(expire_time))
        { // Check timeout
            UART1_error_code = HAL_ERROR_TIMEOUT;
            data_p[0] = 0;
            return;
        }
    }
    data_p[0] = UDR1;
    UART1_error_code = 0;
    UART_DELAY(waittick);
    return;
}

void M128_UART1_read_bytes(uint8_t *data_p, uint8_t sz_data,
                           uint16_t waittick)
{
    HAL_Time expire_time;
    for (int i = 0; i < sz_data; i++)
    {
        HAL_get_expired_time_ms(
            50UL, &expire_time); // Get current time tick (Unit: 1ms)
        while (!(UCSR1A &
                 (1 << RXC1))) // If there is no RX complete flag, Block here
        {
            if (HAL_timeout_test(expire_time))
            { // Check timeout
                UART1_error_code = HAL_ERROR_TIMEOUT;
                data_p[i] = 0;
                return;
            }
        }
        data_p[i] = UDR1;
        UART_DELAY(waittick);
    }
    UART1_error_code = 0;
    return;
}
