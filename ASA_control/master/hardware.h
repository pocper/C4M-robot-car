#include <stdint.h>

/**
 * @brief 初始化擴充版硬體PWM函式
 *
 */
void servo_init();

/**
 * @brief 設定PWM總開關函式
 *
 * @param Enable 禁致能參數，1: 致能，0:禁能
 */
void servo_Power(uint8_t Enable);

/**
 * @brief 更新PWM單一通道函式
 *
 * @param channel 設定通道0~10
 *  - 0 ~  6為手臂伺服機
 *  - 7 ~ 10為輪子伺服機
 * @param val 數值參數(0~6通道為角度[Deg]，7~10為轉速[RPM])
 */
void servo_update();

/**
 * @brief PWM轉換為擴充版晶片數值函式
 *  - 0.50 [ms] ->   0 等份。
 *  - 2.50 [ms] -> 410 等份。
 * @param PWM 波寬調變數值
 * @return uint16_t Tick數值 0 ~ 410
 */
uint16_t PWM2Tick(float PWM);

/**
 * @brief RPM轉換為PWM數值函式
 *
 * @param RPM 轉速，單位[rpm]
 * @return float PWM，單位[ms]
 */
float RPM2PWM(int8_t RPM);

/**
 * @brief RPM轉換至可控範圍數值函式
 *
 * Value range : 0 ~ 75
 * Frequency   : 50Hz per value
 *
 *  Value      PWM [ms]
 *    0    ->  0.5
 *   75    ->  2.5
 *
 * @param RPM 轉速，單位[rpm]
 * @return float Controllable_val，單位[等份]
 */
float RPM2ControllableTable(int8_t RPM);

/*@brief 存放輪子順逆時針之結構體。
 * 若為 +1，則順時針。
 * 若為  0，則停止。
 * 若為 -1，則逆時針。
 **/
typedef struct
{
    int8_t right_front; //右前輪
    int8_t right_rear;  //右後輪
    int8_t left_front;  //左前輪
    int8_t left_rear;   //左後輪
} Wheel;

typedef struct
{
    uint16_t left_front;  // 左前輪中點
    uint16_t right_front; // 右前輪中點
    uint16_t left_rear;   // 左後輪中點
    uint16_t right_rear;  // 右後輪中點
} WheelMid;

typedef struct
{
    uint16_t right_front; // 右前輪正轉
    uint16_t right_rear;  // 右後輪正轉
    uint16_t left_front;  // 左前輪正轉
    uint16_t left_rear;   // 左後輪正轉
} WheelForward;

typedef struct
{
    uint8_t right_front; // 右前輪反轉
    uint8_t right_rear;  // 右後輪反轉
    uint8_t left_front;  // 左前輪反轉
    uint8_t left_rear;   // 左後輪反轉
} WheelBackward;

/**
 * @brief 方便測試用之列舉(enum)
 *
 */
enum
{
    forward,    //前進
    left,       //向左
    backward,   //後退
    right,      //向右
    rotate_ccw, //逆時鐘轉
    rotate_cw   //順時鐘轉
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

void Movement_update();

uint8_t findStr(uint8_t find, void *Data_p);