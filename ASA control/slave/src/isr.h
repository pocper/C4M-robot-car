/**
 * @file isr.h
 * @author LiYu87
 * @date 2019.06.24
 * @brief 巨集 ISR 及 INTERNAL_ISR 實現。
 * 
 * ISR 提供給一般使用者覆寫中斷服務常式。
 * INTERNAL_ISR 提供C4MLIB開發人員覆寫中斷服務常式。
 */

#ifndef C4MLIB_HARDWAR_ISR_H
#define C4MLIB_HARDWAR_ISR_H

// for normal user, it use just like ISR in avrlibc

/* Public Section Start */
#include <avr/interrupt.h>
#undef ISR
#ifdef __cplusplus
#    define ISR(vector, ...)                                                 \
        extern "C" void vector##_routine(void) __attribute__((__INTR_ATTRS)) \
            __VA_ARGS__;                                                     \
        void vector##_routine(void)
#else
#    define ISR(vector, ...)                                                   \
        void vector##_routine(void) __attribute__((__INTR_ATTRS)) __VA_ARGS__; \
        void vector##_routine(void)
#endif
/* Public Section End */

// for lib internal developing
#ifdef __cplusplus
#    define INTERNAL_ISR(vector, ...)                        \
        extern "C" void vector##_routine1(void) __VA_ARGS__; \
        void vector##_routine1(void)
#else
#    define INTERNAL_ISR(vector, ...)             \
        void vector##_routine1(void) __VA_ARGS__; \
        void vector##_routine1(void)
#endif

#endif  // C4MLIB_HARDWAR_ISR_H
