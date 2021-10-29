/**
 * @file pin_def.h
 * @author LiYu87
 * @brief 定義ASA M128 之 ASABUS 的腳位。
 * @date 2019.10.13
 */

#ifndef C4MLIB_ASABUS_M128_PIN_DEF_H
#define C4MLIB_ASABUS_M128_PIN_DEF_H

// ASA BUS ID pins defines
#define ID_PIN PINB
#define ID_DDR DDRB
#define ID_PORT PORTB
#define ID0 PB5
#define ID1 PB6
#define ID2 PB7
#define ID_MASK ((1 << ID0) | (1 << ID1) | (1 << ID2))
#define ID_SHIFT PB5

// ASA BUS IO pins defines
#define BUS_DIO0 PF4
#define BUS_DIO1 PF5
#define BUS_DIO2 PF6
#define BUS_DIO3 PF7
#define BUS_DIO_PIN PINF
#define BUS_DIO_DDR DDRF
#define BUS_DIO_PORT PORTF
#define BUS_DIO_MASK \
    _BV(BUS_DIO0) | _BV(BUS_DIO1) | _BV(BUS_DIO2) | _BV(BUS_DIO3)
#define BUS_DIO_SHIFT BUS_DIO0

// 6 Pin GPIO 特用功能
// DIO0 - PF4 - ASA SPI CS
// DIO1 - PF5 - ASA 485 I/O 切換
// DIO2 - PF6 - ASA介面卡主動中斷訊號(無隔離)
// DIO3 - PF7 - ASA介面卡主動中斷訊號(無隔離)
// DIO4 - PG3 - /RD
// DIO5 - PG4 - /WR - Software reset

// ASA BUS CS pins defines
#define ASA_CS PB4
#define ASA_CS_PIN PINB
#define ASA_CS_DDR DDRB
#define ASA_CS_PORT PORTB
#define ASA_CS_MASK (1 << ASA_CS)
#define ASA_CS_SHIFT ASA_CS

// ASA BUS CS Expension pins defines (For ASA_ID not in 0~7)
#define ASA_CS_DDR_ID_8     DDRB
#define ASA_CS_ID_8         PB4
#define ASA_CS_PORT_ID_8    PORTB
#define ASA_CS_DDR_ID_9     DDRB
#define ASA_CS_ID_9         PB5
#define ASA_CS_PORT_ID_9    PORTB
#define ASA_CS_DDR_ID_10    DDRB
#define ASA_CS_ID_10        PB6
#define ASA_CS_PORT_ID_10   PORTB
#define ASA_CS_DDR_ID_11    DDRB
#define ASA_CS_ID_11        PB7
#define ASA_CS_PORT_ID_11   PORTB

// ASA BUS SPI pin defines
#define BUS_SPI_PORT PORTB
#define BUS_SPI_PIN PINB
#define BUS_SPI_DDR DDRB
#define BUS_SPI_MISO PB3
#define BUS_SPI_MOSI PB2
#define BUS_SPI_SCK PB1
#define BUS_SPI_SS PB0
#define BUS_SPI_MASK \
    _BV(BUS_SPI_MISO) | _BV(BUS_SPI_MOSI) | _BV(BUS_SPI_SCK) | _BV(BUS_SPI_SS)
#define BUS_SPI_SHIFT 0
#define BUS_SPI_OUT _BV(BUS_SPI_MOSI) | _BV(BUS_SPI_SCK) | _BV(BUS_SPI_SS)

#endif  // C4MLIB_ASABUS_M128_PIN_DEF_H
