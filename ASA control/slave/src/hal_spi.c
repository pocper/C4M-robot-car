/**
 * @file hal_spi.c
 * @author Deng Xiang-Guan
 * @date 2019.01.05
 * @brief Implement a hardware abstraction layer for atmega128.
 */

#include "hal_spi.h"

#include "asabus.h"
#include "pin_def.h"
#include "debug.h"
#include "isr.h"
#include "std_res.h"
#include "hal_time.h"

#include <avr/io.h>
#include <stddef.h>

/**
 * @defgroup hw_hal_spi_func hardware hal spi functions
 */

/**
 * @brief M128 SPI Master初始化函式。
 *
 * @ingroup hw_hal_spi_func
 */
static void M128_SPI_Master_init(void);

/**
 * @brief M128 SPI Slave初始化函式。
 *
 * @ingroup hw_hal_spi_func
 */
static void M128_SPI_Slave_init(void);

/**
 * @brief M128 SPI 單筆資料交換函式。
 *
 * @ingroup hw_hal_spi_func
 * @param data      欲交換資料。
 * @return uint8_t  依照是否超過timeout時間決定回傳值。
 *                  - 超過timeout時間 : 0。
 *                  - timeout時間 : SPDR。
 */
static uint8_t M128_SPI_swap(uint8_t data);

/**
 * @brief M128 SPI 多筆資料交換(送+收)函式。
 *
 * @ingroup hw_hal_spi_func
 * @param trm_data      欲送出資料指標。
 * @param rec_data      欲接收資料指標。
 * @param sizeOfData    資料大小。
 */
static void M128_SPI_multi_swap(uint8_t *trm_data, uint8_t *rec_data,
                                uint8_t sizeOfData);

/**
 * @brief M128 SPI 單筆送資料函式。
 *
 * @ingroup hw_hal_spi_func
 * @param data  欲送出資料。
 */
static void M128_SPI_write_byte(uint8_t data);

/**
 * @brief M128 SPI 多筆送資料函式。
 *
 * @ingroup hw_hal_spi_func
 * @param data_p        欲送出資料指標。
 * @param sizeOfData    欲送出資料大小。
 */
static void M128_SPI_write_multi_bytes(uint8_t *data_p, uint8_t sizeOfData);

/**
 * @brief M128 SPI 單筆資料接收函式。
 *
 * @ingroup hw_hal_spi_func
 * @return uint8_t  依照是否超過timeout時間決定回傳值。
 *                  - 超過timeout時間 : 0。
 *                  - timeout時間內 : SPDR。
 */
static uint8_t M128_SPI_read_byte(void);
/**
 * @brief M128 SPI 多筆資料接收函式。
 *
 * @ingroup hw_hal_spi_func
 * @param data_p        欲接收資料指標。
 * @param sizeOfData    欲接收資料大小。
 */
static void M128_SPI_read_multi_bytes(uint8_t *data_p, uint8_t sizeOfData);

/**
 * @brief M128 SPI 致能ASAID對應SPI裝置驅動函式。
 *
 * @ingroup hw_hal_spi_func
 * @param id    旋鈕對應ASAID。
 *
 */
static void M128_SPI_enable_cs(char id);

/**
 * @brief M128 SPI 禁能ASAID對應SPI裝置驅動函式。
 *
 * @ingroup hw_hal_spi_func
 * @param id    旋鈕對應ASAID。
 */
static void M128_SPI_disable_cs(char id);

/**
 * @brief slave端  寫入master
 *
 * @return uint8_t  SPDR
 */
static uint8_t M128_SPIS_read_byte(void);

/**
 * @brief slave端  回傳SPDR暫存器內容
 *
 * @param sendData  欲寫入資料
 */
static void M128_SPIS_write_byte(uint8_t sendData);

TypeOfMasterSPIInst SPI_MasterInst = {
    .init = M128_SPI_Master_init,
    .spi_swap = M128_SPI_swap,
    .spi_multi_swap = M128_SPI_multi_swap,
    .spi_compelete_cb = 0,
    .write_byte = M128_SPI_write_byte,
    .write_multi_bytes = M128_SPI_write_multi_bytes,
    .read_byte = M128_SPI_read_byte,
    .read_multi_bytes = M128_SPI_read_multi_bytes,
    .enable_cs = M128_SPI_enable_cs,
    .disable_cs = M128_SPI_disable_cs};

TypeOfSlaveSPIInst SPI_SlaveInst = {.init = M128_SPI_Slave_init,
                                    .spi_compelete_cb = 0,
                                    .write_byte = M128_SPIS_write_byte,
                                    .read_byte = M128_SPIS_read_byte};

static void M128_SPI_Master_init(void)
{
    // Initialize SPI ID
    ASABUS_ID_init();
    // Setup SPI pins
    DDRB |= (1 << BUS_SPI_MOSI) | (1 << BUS_SPI_SCK) | (1 << BUS_SPI_SS);
    DDRB &= ~(1 << BUS_SPI_MISO);
    // default Master CS pin is PF4
    ASA_CS_DDR |= (1 << ASA_CS);
    // SCK oscillator frequency divided 128
    // SPI Master mode
    // Enable SPI
    SPCR0 |= (1 << SPR0) | (1 << SPR1) | (1 << MSTR) | (1 << SPE);
}

static void M128_SPI_Slave_init(void)
{
    DDRB &= ~(1 << BUS_SPI_MOSI) & ~(1 << BUS_SPI_SCK) & ~(1 << BUS_SPI_SS);
    DDRB |= (1 << BUS_SPI_MISO);
    // Enable SPI
    SPCR0 = (1 << SPE);
    SPCR0 |= (1 << SPIE);
    sei();
}

static uint8_t M128_SPI_swap(uint8_t data)
{
    SPDR0 = data;
    HAL_Time expire_time;
    HAL_get_expired_time_ms(50UL,
                            &expire_time); // Get current time tick (Unit: 1ms)
    while (!(SPSR0 & (1 << SPIF)))
    {
        if (HAL_timeout_test(expire_time))
        { // Check timeout
            SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
            DEBUG_INFO("SPI swap TIMEOUT\n");
            return 0;
        }
    }
    return SPDR0;
}

static void M128_SPI_multi_swap(uint8_t *trm_data, uint8_t *rec_data,
                                uint8_t sizeOfData)
{
    do
    {
        SPDR0 = *(trm_data++);
        HAL_Time expire_time;
        HAL_get_expired_time_ms(
            50UL, &expire_time); // Get current time tick (Unit: 1ms)
        while (!(SPSR0 & (1 << SPIF)))
        {
            if (HAL_timeout_test(expire_time))
            { // Check timeout
                SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
                DEBUG_INFO("SPI swap TIMEOUT\n");
                return;
            }
        }
        *(rec_data++) = SPDR0;
    } while (--sizeOfData);
}

static void M128_SPI_write_byte(uint8_t data)
{
    SPDR0 = data;
    HAL_Time expire_time;
    HAL_get_expired_time_ms(50UL,
                            &expire_time); // Get current time tick (Unit: 1ms)
    while (!(SPSR0 & (1 << SPIF)))
    {
        if (HAL_timeout_test(expire_time))
        { // Check timeout
            SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
            DEBUG_INFO("SPI swap TIMEOUT\n");
            return;
        }
    }
}

static void M128_SPI_write_multi_bytes(uint8_t *data_p, uint8_t sizeOfData)
{
    do
    {
        SPDR0 = *(data_p++);
        HAL_Time expire_time;
        HAL_get_expired_time_ms(
            50UL, &expire_time); // Get current time tick (Unit: 1ms)
        while (!(SPSR0 & (1 << SPIF)))
        {
            if (HAL_timeout_test(expire_time))
            { // Check timeout
                SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
                DEBUG_INFO("SPI swap TIMEOUT\n");
                return;
            }
        }
    } while (--sizeOfData);
}

static uint8_t M128_SPI_read_byte(void)
{
    HAL_Time expire_time;
    HAL_get_expired_time_ms(50UL,
                            &expire_time); // Get current time tick (Unit: 1ms)
    while (!(SPSR0 & (1 << SPIF)))
    {
        if (HAL_timeout_test(expire_time))
        { // Check timeout
            SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
            DEBUG_INFO("SPI swap TIMEOUT\n");
            return 0;
        }
    }
    return SPDR0;
}

static void M128_SPI_read_multi_bytes(uint8_t *data_p, uint8_t sizeOfData)
{
    do
    {
        HAL_Time expire_time;
        HAL_get_expired_time_ms(
            50UL, &expire_time); // Get current time tick (Unit: 1ms)
        while (!(SPSR0 & (1 << SPIF)))
        {
            if (HAL_timeout_test(expire_time))
            { // Check timeout
                SPI_MasterInst.error_code = HAL_ERROR_TIMEOUT;
                DEBUG_INFO("SPI swap TIMEOUT\n");
                return;
            }
        }
        *(data_p++) = SPDR0;
    } while (--sizeOfData);
}

static void M128_SPI_enable_cs(char id)
{
    if (id >= 8)
    {
        switch (id)
        {
        case 8:
            // Master CS pin is PB4
            ASA_CS_DDR_ID_8 |= (1 << ASA_CS_ID_8);
            ASA_CS_PORT_ID_8 &= ~(1 << ASA_CS_ID_8);
            break;
        case 9:
            // Master CS pin is PB5
            ASA_CS_PORT_ID_9 |= (1 << ASA_CS_ID_9);
            ASA_CS_PORT_ID_9 &= ~(1 << ASA_CS_ID_9);
            break;
        case 10:
            // Master CS pin is PB6
            ASA_CS_PORT_ID_10 |= (1 << ASA_CS_ID_10);
            ASA_CS_PORT_ID_10 &= ~(1 << ASA_CS_ID_10);
            break;
        case 11:
            // Master CS pin is PB7
            ASA_CS_PORT_ID_11 |= (1 << ASA_CS_ID_11);
            ASA_CS_PORT_ID_11 &= ~(1 << ASA_CS_ID_11);
            break;
        default:
            break;
        }
    }
    else
    {
        ASABUS_ID_set(id);
        ASA_CS_PORT &= ~(1 << ASA_CS);
    }
}

static void M128_SPI_disable_cs(char id)
{
    if (id >= 8)
    {
        switch (id)
        {
        case 8:
            // Master CS pin is PB4
            ASA_CS_DDR_ID_8 |= (1 << ASA_CS_ID_8);
            ASA_CS_PORT_ID_8 |= (1 << ASA_CS_ID_8);
            break;
        case 9:
            // Master CS pin is PB5
            ASA_CS_DDR_ID_9 |= (1 << ASA_CS_PORT_ID_9);
            ASA_CS_PORT_ID_9 |= (1 << ASA_CS_ID_9);
            break;
        case 10:
            // Master CS pin is PB6
            ASA_CS_DDR_ID_10 |= (1 << ASA_CS_ID_10);
            ASA_CS_PORT_ID_10 |= (1 << ASA_CS_ID_10);
            break;
        case 11:
            // Master CS pin is PB7
            ASA_CS_DDR_ID_11 |= (1 << ASA_CS_ID_11);
            ASA_CS_PORT_ID_11 |= (1 << ASA_CS_ID_11);
            break;
        default:
            break;
        }
    }
    else
    {
        ASA_CS_PORT |= (1 << ASA_CS);
    }
}

static void M128_SPIS_write_byte(uint8_t sendData)
{
    SPDR0 = sendData;
}

static uint8_t M128_SPIS_read_byte(void)
{
    return SPDR0;
}
