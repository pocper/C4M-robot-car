/**
 * @file hal_spi.h
 * @author Deng Xiang-Guan
 * @date 2019.10.07
 * @brief Create a hardware abstraction layer to separate hardware dependent.
 */

#ifndef C4MLIB_HARDWARE_HAL_SPI_H
#define C4MLIB_HARDWARE_HAL_SPI_H

#include <stdint.h>

#define SPI_TIMEOUT_TIME \
    50UL  ///< SPI timeout時間                  @ingroup asaspi_macro
#define SPI_CF_MAX_BITS \
    0x07  ///< SPI control flag                 @ingroup asaspi_macro
#define SPI_CF_MASK \
    0x07  ///< SPI control flag                 @ingroup asaspi_macro
#define SPI_CF_MSB_MAX_BITS \
    0x1F  ///< SPI control flag                 @ingroup asaspi_macro
#define SPI_CF_MSB_MASK \
    0x1F  ///< SPI control flag                 @ingroup asaspi_macro

/**
 * @defgroup hw_hal_spi_struct hardware hal spi struct
 */

/**
 * @brief SPI Master 抽象層結構定義
 *
 * @ingroup hw_hal_struct
 * @ingroup hw_hal_spi_struct
 */
typedef struct {
    void (*init)(void);                                             ///< SPI Master初始化函式指標
    uint8_t (*spi_swap)(uint8_t data);                              ///< SPI Master單筆資料交換函式指標
    void (*spi_multi_swap)(
        uint8_t* trm_data, uint8_t* rec_data, uint8_t sizeOfData);  ///< SPI Master多筆資料交換(送+收)函式指標
    void (*spi_compelete_cb)(void);                                 ///< SPI Master call back函式指標
    void (*write_byte)(uint8_t data);                               ///< SPI Master送出單筆資料函式指標
    void (*write_multi_bytes)(uint8_t* data_p, uint8_t sizeOfData); ///< SPI Master送出多筆資料函式指標
    uint8_t (*read_byte)(void);                                     ///< SPI Master接收單筆資料函式指標
    void (*read_multi_bytes)(uint8_t* data_p, uint8_t sizeOfData);  ///< SPI Master接收多筆資料函式指標
    void (*enable_cs)(char id);                                     ///< SPI Master致能cs腳位函式指標
    void (*disable_cs)(char id);                                    ///< SPI Master禁能cs腳位函式指標
    uint8_t error_code;                                             ///< 錯誤代碼
} TypeOfMasterSPIInst;

/**
 * @brief SPI Slave 抽象層結構定義
 *
 * @ingroup hw_hal_struct
 * @ingroup hw_hal_spi_struct
 */
typedef struct {
    void (*init)(void);                 ///< SPI Slave初始化函式指標
    void (*spi_compelete_cb)(void);     ///< SPI Slave call back函式指標
    void (*write_byte)(uint8_t data);   ///< SPI Slave寫入資料函式指標
    uint8_t (*read_byte)(void);         ///< SPI Slave讀取資料函式指標
    uint8_t* echo_p;                    ///< SPI Slave回應值
    uint8_t error_code;                 ///< 錯誤代碼
} TypeOfSlaveSPIInst;

extern TypeOfMasterSPIInst SPI_MasterInst;
extern TypeOfSlaveSPIInst SPI_SlaveInst;

#endif /* C4MLIB_HARDWARE_HAL_SPI_H */
