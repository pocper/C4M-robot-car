/**
 * @file hal_time.h
 * @author Ye cheng-Wei
 * @date 2018.11.12
 * @brief Create a Abstraction Timer for timeout useag.
 *
 *
 */

#ifndef C4MLIB_TIME_HAL_TIME_H
#define C4MLIB_TIME_HAL_TIME_H

#include <stdint.h>

#define HAL_TIME_UNIT_MICROSECOND (1000UL)
#define HAL_TIMEOUT 1

typedef uint32_t HAL_Time;

void HAL_time_init();

HAL_Time HAL_get_time();

void HAL_get_expired_time_us(uint32_t duration_us, uint32_t *p_expired_time);

void HAL_get_expired_time_ms(uint32_t duration_ms, uint32_t *p_expired_time);

uint8_t HAL_timeout_test(HAL_Time expire_time);

void HAL_delay(uint32_t duration_ms);

void HAL_tick();

#endif  // C4MLIB_TIME_HAL_TIME_H
