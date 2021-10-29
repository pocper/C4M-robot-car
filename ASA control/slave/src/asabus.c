/**
 * @file asabus.c
 * @author LiYu87
 * @brief asabus 相關硬體操作函式在不同硬體平台上實現的分割。
 * @date 2019.10.13
 */

#if defined(__AVR_ATmega128__)
#    include "io.c"
#    include "spi.c"
#    include "twi.c"
#    include "uart.c"
#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega48__) || \
    defined(__AVR_ATmega168__)
#    include "m88/io.c"
#    include "m88/spi.c"
#    include "m88/twi.c"
#    include "m88/uart.c"
#elif defined(__AVR_ATtiny2313__)
#    include "tiny2313/io.c"
#    include "tiny2313/spi.c"
#    include "tiny2313/twi.c"
#    include "tiny2313/uart.c"
#else
#    if !defined(__COMPILING_AVR_LIBC__)
#        warning "device type not defined"
#    endif
#endif
