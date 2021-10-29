/**
 * @file bits_op.h
 * @author LiYu87, cy023
 * @date 2021.01.28
 * @brief Provide standard bitswise operation.
 */

#ifndef C4MLIB_MACRO_BITS_OP_H
#define C4MLIB_MACRO_BITS_OP_H

/**
 * @defgroup macro_macro
 */

/* Public Section Start */
/**
 * @def SETBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief 將 ADDRESS 指定的 BIT 設置為 1。
 */
#define SETBIT(ADDRESS, BIT) ((ADDRESS) |= (1 << BIT))

/**
 * @def CLRBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief 將 ADDRESS 指定的 BIT 清除為 0。
 */
#define CLRBIT(ADDRESS, BIT) ((ADDRESS) &= ~(1 << BIT))

/**
 * @def CHKBIT(ADDRESS, BIT)
 * @ingroup macro_macro
 * @brief 檢查 ADDRESS 指定的 BIT 是 1 或 0。
 */
#define CHKBIT(ADDRESS, BIT) (((ADDRESS) & (1 << BIT)) == (1 << BIT))

/**
 * @def REGFPT(REG_P, MASK, SHIFT, DATA)
 * @ingroup macro_macro
 * @brief 依照指定的 MASK, SHIFT, DATA 去讀取暫存器
 */
#define REGFPT(REG_P, MASK, SHIFT, DATA)                                       \
    (*((volatile char *)REG_P) = ((*((volatile char *)REG_P) & (~MASK)) |      \
                                  (((DATA) << (SHIFT)) & (MASK))))

/**
 * @def REGFGT(REG_P, MASK, SHIFT, DATA_P)
 * @ingroup macro_macro
 * @brief 依照指定的 MASK, SHIFT, DATA_P 去寫入暫存器
 */
#define REGFGT(REG_P, MASK, SHIFT, DATA_P)                                     \
    (*((volatile char *)DATA_P) =                                              \
         ((*((volatile char *)REG_P) & (MASK)) >> (SHIFT)))

/**
 * @def REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照指定BYTES數的 *DATA_P 去寫入暫存器 *REG_P 。
 */
#define REGPUT(REG_P, BYTES, DATA_P)                                           \
    do {                                                                       \
        for (signed char __putptr = BYTES - 1; __putptr >= 0; __putptr--) {    \
            *((volatile char *)REG_P + __putptr) =                             \
                *((volatile char *)DATA_P + __putptr);                         \
        }                                                                      \
    } while (0)

/**
 * @def HF_REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照先高後低的順序，將指定BYTES數的 *DATA_P 去寫入暫存器 *REG_P。
 *        同 REGPUT。
 */
#define HF_REGPUT(REG_P, BYTES, DATA_P)                                        \
    do {                                                                       \
        for (signed char __putptr = BYTES - 1; __putptr >= 0; __putptr--) {    \
            *((volatile char *)REG_P + __putptr) =                             \
                *((volatile char *)DATA_P + __putptr);                         \
        }                                                                      \
    } while (0)

/**
 * @def LF_REGPUT(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照先低後高的順序，將指定BYTES數的 *DATA_P 去寫入暫存器 *REG_P。
 */
#define LF_REGPUT(REG_P, BYTES, DATA_P)                                        \
    do {                                                                       \
        for (signed char __putptr = 0; __putptr < BYTES; __putptr++) {    \
            *((volatile char *)REG_P + (BYTES - __putptr - 1)) =               \
                *((volatile char *)DATA_P + __putptr);                         \
        }                                                                      \
    } while (0)

/**
 * @def REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照指定BYTES數從暫存器 *REG_P 取得數值存入DATA_P。
 */
#define REGGET(REG_P, BYTES, DATA_P)                                           \
    do {                                                                       \
        for (signed char __getptr = 0; __getptr < BYTES; __getptr++) {         \
            *((volatile char *)DATA_P + __getptr) =                            \
                *((volatile char *)REG_P + __getptr);                          \
        }                                                                      \
    } while (0)

/**
 * @def HF_REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照先高後低的順序，將指定BYTES數從暫存器 *REG_P 取得數值存入DATA_P。
 */
#define HF_REGGET(REG_P, BYTES, DATA_P)                                        \
    do {                                                                       \
        for (signed char __getptr = BYTES - 1; __getptr >= 0; __getptr--) {    \
            *((volatile char *)DATA_P + (BYTES - __getptr - 1)) =              \
                *((volatile char *)REG_P + __getptr);                          \
        }                                                                      \
    } while (0)

/**
 * @def LF_REGGET(REG_P, BYTES, DATA_P)
 * @ingroup macro_macro
 * @brief 依照先低後高的順序，將指定BYTES數從暫存器 *REG_P 取得數值存入DATA_P。
 *        同 REGGET。
 */
#define LF_REGGET(REG_P, BYTES, DATA_P)                                        \
    do {                                                                       \
        for (signed char __getptr = 0; __getptr < BYTES; __getptr++) {         \
            *((volatile char *)DATA_P + __getptr) =                            \
                *((volatile char *)REG_P + __getptr);                          \
        }                                                                      \
    } while (0)

/**
 * @def HIBYTE16(SOURCE)
 * @ingroup macro_macro
 * @brief
 */
#define HIBYTE16(SOURCE) (SOURCE >> 8)

/**
 * @def LOBYTE16(SOURCE)
 * @ingroup macro_macro
 * @brief
 */
#define LOBYTE16(SOURCE) (SOURCE & 0xff)
/* Public Section End */

#endif  // C4MLIB_MACRO_BITS_OP_H
