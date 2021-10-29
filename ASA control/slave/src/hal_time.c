#include "hal_time.h"

#include "debug.h"

volatile HAL_Time HAL_time_global;

void HAL_time_init() {
    HAL_time_global = 0;
    return;
}

HAL_Time HAL_get_time() {
    return HAL_time_global;
}

void HAL_get_expired_time_us(uint32_t duration_us, uint32_t* p_expired_time) {
    DEBUG_INFO("HAL_get_expired_time_us test : %ld, %ld \n", HAL_time_global,
               HAL_time_global + duration_us / HAL_TIME_UNIT_MICROSECOND);
    *p_expired_time = HAL_time_global + duration_us / HAL_TIME_UNIT_MICROSECOND;

    return;
}

void HAL_get_expired_time_ms(uint32_t duration_ms, uint32_t* p_expired_time) {
    DEBUG_INFO("HAL_get_expired_time_ms test : %ld, %ld \n", HAL_time_global,
               HAL_time_global + duration_ms);
    *p_expired_time = HAL_time_global + duration_ms;

    return;
}

uint8_t HAL_timeout_test(HAL_Time expire_time) {
    DEBUG_INFO("Time test : %ld, %ld \n", HAL_time_global, expire_time);
    if (HAL_time_global > expire_time)
        return HAL_TIMEOUT;
    else
        return 0;
}

void HAL_delay(uint32_t duration_ms) {
    uint32_t expired_time = 0;
    HAL_get_expired_time_ms(duration_ms, &expired_time);
    DEBUG_INFO("%lu : %lu\n", HAL_time_global, expired_time);
    while (HAL_time_global < expired_time) {
        DEBUG_INFO("| %lu : %lu\n", HAL_time_global, expired_time);
    }  // Block here
    return;
}

void HAL_tick() {
    HAL_time_global++;
    return;
}
