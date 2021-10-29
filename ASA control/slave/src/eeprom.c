/**
 * @file eeprom.c
 * @author LiYu87
 * @date 2019.10.07
 * @brief eeprom相關函式實作
 */

#include "eeprom.h"

#include <avr/eeprom.h>

// TODO: HARDWARE EEPROM 尋找負責人，或安排時程

void EEPROM_set(int Address, char Bytes, void *Data_p) {
    eeprom_write_block(Data_p, (uint8_t *)Address, Bytes);
}

void EEPROM_get(int Address, char Bytes, void *Data_p) {
    eeprom_read_block(Data_p, (uint8_t *)Address, Bytes);
}
