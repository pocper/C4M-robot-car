#ifndef _C4MLIB_H
#define _C4MLIB_H
#include "c4mlib.h"
#endif

#ifndef _SERVO_H
#define _SERVO_H
#include "servo.h"
#endif

/**
 * @brief 存放輪子順逆時針之結構體
 *        若為正，則順時針
 *        若為負，則逆時針
 * 
 */
typedef struct
{
    int left_front;  //左前輪
    int right_front; //右前輪
    int left_rear;   //左後輪
    int right_rear;  //右後輪
} Wheel;

/**
 * @brief 方便測試用之列舉(enum)
 * 
 */
enum
{
    forward,      //前進
    left,         //向左
    backward,     //後退
    right,        //向右
    left_front,   //左前
    right_front,  //右前
    right_behind, //左後
    left_behind,  //右後
    rotate_cw,    //順時鐘轉
    rotate_ccw,   //逆時鐘轉
};

/**
 * @brief 更新輪子轉向函式
 * 
 * @param Dir 輸入0~9方向
 * 對應內容為：WASDQEZC
 *  - 1 -> W  前進
 *  - 2 -> A  向左
 *  - 3 -> S  後退
 *  - 4 -> D  向右
 *  - 5 -> Q  左前
 *  - 6 -> E  右前
 *  - 7 -> Z  左後
 *  - 8 -> C  右後
 *  - 9 -> R  順時鐘轉
 *  -尚未設計　逆時鐘轉
 *  
 *   Q      W      E
 *     \    |    /
 *       \  |  /
 *   A-------------D
 *       /  |  \
 *     /    |    \
 *   Z      S      C
 */
void Movement_condition(int Dir);

/**
 * @brief 輸出輪子順逆時針結構體
 * 
 */
void Movement_update();

/**
 * @brief 更新手臂角度位置及
 *        條件判斷避免超過伺服機可輸出之PWM範圍
 * 
 * @param channel 設定角度之腳位1(PB1)~7(PB7)
 * @param Degree 設定之角度(單位：度)
 * @return uint8_t 錯誤代碼：
 */
uint8_t Rotation_update(uint8_t channel, int8_t Degree);