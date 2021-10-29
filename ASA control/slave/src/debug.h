/**
 * @file debug.h
 * @author LiYu87
 * @date 2019.03.27
 * @brief 提供函式庫開發人員DEBUG的輸出入介面
 *
 * 在 make 時期加入參數 DEBUG=1，便可以啟用DEBUG輸出功能。
 */

#ifndef C4MLIB_DEBUG_DEBUG_H
#define C4MLIB_DEBUG_DEBUG_H

#ifdef USE_C4MLIB_DEBUG
#    define DEBUG_INFO(format, args...) printf("[DEBUG] " format, ##args)
#else
#    define DEBUG_INFO(args...)
#endif

#endif  // C4MLIB_DEBUG_DEBUG_H
