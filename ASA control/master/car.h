#include <stdint.h>

#define TotalTask 2 //車斗 | 車輪

/**
 * @brief 暫停結構體
 * @param Counter[TotalTask] 計數器目前數值
 * @param Target[TotalTask]  計數器上限數值
 *
 */
typedef struct
{
    uint8_t Counter[TotalTask];
    uint8_t Target[TotalTask];
} Task;

/**
 * @brief 存放輪子順逆時針之結構體。
 *        若為 +1，則順時針。
 *        若為  0，則停止。
 *        若為 -1，則逆時針。
 *
 */
typedef struct
{
    int8_t left_front;  //左前輪
    int8_t right_front; //右前輪
    int8_t left_rear;   //左後輪
    int8_t right_rear;  //右後輪
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
 * @param uint8_t Dir 輸入0 ~ 10方向。
 * 對應內容為：WASDQEZCV。
 *  - 1 -> W  前進。
 *  - 2 -> A  向左。
 *  - 3 -> S  後退。
 *  - 4 -> D  向右。
 *  - 5 -> Q  左前。
 *  - 6 -> E  右前。
 *  - 7 -> Z  左後。
 *  - 8 -> C  右後。
 *  - 9 -> R  順時鐘轉。
 *  -10 -> V　逆時鐘轉。
 *
 *   Q      W      E
 *     \    |    /
 *       \  |  /
 *   A-------------D
 *       /  |  \
 *     /    |    \
 *   Z      S      C
 */
void Movement_condition(uint8_t Dir);

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
 */
void Rotation_update(uint8_t channel, int8_t Degree);

/**
 * @brief 由起點至終點進行內插法並輸出至伺服機
 *
 * @param channel 設定角度之腳位1(PB1)~7(PB7)
 * @param dest_Degree 設定終點之角度(單位：度)
 */
void interpolation(uint8_t channel, int8_t dest_Degree);

/**
 * @brief 伺服機暫停功能方塊初始化
 *
 */
void task_init();