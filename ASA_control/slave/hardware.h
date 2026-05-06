#include <stdint.h>

#define servo_num 16

#define RegAdd_num 9
#define EEPROM_RegAdd_num 4

#define ASAUART_CMD_HEADER 0xAA
#define ASAUART_RSP_OK 0

#define EEPROM_ADDRESS_OFFSET_UARTID 0x00
#define EEPROM_ADDRESS_OFFSET_MINLIMIT 0x01
#define EEPROM_ADDRESS_OFFSET_MAXLIMIT 0x21
#define EEPROM_ADDRESS_OFFSET_CURRENTPROTECT 0x41

#define ADC_SING_CHAN_CONVERT_TIMES 3

/**
 * @brief PCA9685晶片初始化函式
 *
 */
void PCA9685_init();

/**
 * @brief PCA9685晶片更新PWM函式
 *
 */
void PCA9685_update();

void PowerRelay_init();

void PowerRelay_update();

void DCPlugInDetect_init();

void DCPlugInDetect_update();

void ADC_init();

void ADC_update();

void ADC_value_printf();

void ADG794_init();

void CurrentProtect_update();

void RegAdd_init();

// void EEPROM_init();

// void EEPROM_Flash();

void EEPROM_read();

void tmp_EEPROM_read();

void EEPROM_read_printf();

void EEPROM_update();