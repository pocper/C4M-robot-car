/**
 * @file io.c
 * @author LiYu87
 * @brief ASA M128 之ASABUS IO 之硬體初始化。
 * @date 2019.10.13
 */

#include "asabus.h"
#include "pin_def.h"
#include "bits_op.h"
#include "std_res.h"

#include <avr/io.h>

void ASABUS_ID_set(char id) {
    if (id > 0x07) {
        return;
    }
    else {
        REGFPT(&ID_PORT, ID_MASK, ID_SHIFT, id);
    }
};

void ASABUS_ID_init(void) {
    REGFPT(&ID_DDR, ID_MASK, ID_SHIFT, 7);
};
