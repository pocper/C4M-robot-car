/**
 * @file std_res.h
 * @author LiYu87
 * @date 2019.01.28
 * @brief Provide ASA standard function response number.
 */

#ifndef C4MLIB_MACRO_STD_RES_H
#define C4MLIB_MACRO_STD_RES_H

// set, fpt, fgt, put, get 函式的標準回傳值
#define RES_OK 0x00            ///< 0 正確  @ingroup macro_macro
#define RES_ERROR_ID 0x01      ///< 1 參數 ASAID 超出範圍  @ingroup macro_macro
#define RES_ERROR_LSBYTE 0x02  ///< 2 參數 LSByte 錯誤  @ingroup macro_macro
#define RES_ERROR_BYTES 0x03   ///< 3 參數 Bytes 錯誤  @ingroup macro_macro
#define RES_ERROR_MASK 0x04    ///< 4 參數 Mask 超出範圍  @ingroup macro_macro
#define RES_ERROR_SHIFT 0x05   ///< 5 參數 Shift 超出範圍  @ingroup macro_macro

#define RES_ERROR_COMU 0x06  ///< 6 通訊錯誤  @ingroup macro_macro

// UART, SPI, TWI HAL 函式的標準回傳值
#define HAL_OK 0x00                         ///< 0 正確  @ingroup macro_macro
#define HAL_ERROR_TIMEOUT 0x01              ///< 1 @ingroup macro_macro
#define HAL_ERROR_CHK 0x02                  ///< 2 @ingroup macro_macro
#define HAL_ERROR_CHK_SUM 0x03              ///< 3 @ingroup macro_macro
#define HAL_ERROR_DEVICE_ID_NOT_FOUND 0x04  ///< 4 @ingroup macro_macro
#define HAL_ERROR_MODE_SELECT 0x05          ///< 5 @ingroup macro_macro
#define HAL_ERROR_HEADER 0x06               ///< 6 @ingroup macro_macro
#define HAL_ERROR_ADDR 0x07                 ///< 7 @ingroup macro_macro
#define HAL_ERROR_BYTES 0x08                ///< 8 @ingroup macro_macro
#define HAL_ERROR_SHIFT 0x09                ///< 9 @ingroup macro_macro

// Interrupt net 函式的標準回傳值
#define INT_OK 0x00                     ///< 0 正確  @ingroup macro_macro
#define INT_ERROR_POINTER_IS_NULL 0xff  ///< 0xff   @ingroup macro_macro
#define INT_ERROR_ISR_EXCEED 0x02       ///< 2      @ingroup macro_macro
#define INT_ERROR_NUM_EXCEED 0xfe       ///< 0xfe   @ingroup macro_macro

#endif  // C4MLIB_MACRO_STD_RES_H
