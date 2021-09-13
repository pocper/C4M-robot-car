#include "c4mlib.h"
#include <string.h>

#define deg_PWM_DIV 200
#define spd_PWM_DIV 75

#define Servo_STOP 127
#define CH_num 3 //車輪 車斗 手臂
#define maxReceieveBuffer 100

/**
 * @brief PWM輸出陣列結構體
 * @param PWMTableB 8通道PWM輸出旗標表，
 *                  每一矩陣元素對應不同時間點之HI/LOW，
 *                  因有同時八通道輸出所以uint8_t
 * @param PWM_BASICHI 紀錄速度為零的腳位為0；否則為1
 * 
 */
typedef struct
{
    uint8_t PWMTableB[deg_PWM_DIV];
    uint8_t PWM_BASICHI;
} my_PWMStr_t;

/**
 * @brief 暫停結構體
 * @param counter[CH_num] 計數器目前數值
 * @param Target[CH_num]  計數器上限數值
 * 
 */
typedef struct
{
    uint8_t counter[CH_num];
    uint8_t Target[CH_num];
} Task;

/**
 * @brief 伺服機暫停功能方塊初始化
 * 
 */
void Task_init();

/**
 * @brief 初始化設定Timer1，
 *        目前為輸出角度之PWM
 * 
 */
void timer1_init();

/**
 * @brief 初始設定Timer2，
 *        目前為伺服機暫停功能
 * 
 */
void timer2_init();

/**
 * @brief 初始設定Timer3，
 *        目前為輸出速度之PWM
 * 
 */
void timer3_init();

/**
 * @brief 有限角伺服機數值輸出函式
 * 
 * @param channel 設定角度之腳位1(PB1)~7(PB7)
 * @param degree 設定之角度(單位：度)
 * @return uint8_t 錯誤代碼：
 */
uint8_t Servo_Degree_set(uint8_t channel, int8_t degree);

/**
 * @brief 無限角伺服機數值輸出函式
 * 
 * @param channel 設定速度之腳位4(PD4)~7(PD7)
 * @param speed 設定之速度(單位：RPM)
 * @return uint8_t 錯誤代碼：
 */
uint8_t Servo_Speed_set(uint8_t channel, int8_t speed);

/**
 * @brief 角度換算成PWM波寬數值轉換函式
 * 
 * @param Degree 角度(單位：度)
 * @return uint8_t 錯誤代碼：
 */
uint8_t Degree2Width(int8_t Degree);

/**
 * @brief RPM換算成PWM波寬數值轉換函式
 * 
 * @param rpm 速度(單位：RPM)
 * @return uint8_t 錯誤代碼：
 */
uint8_t RPM2Width(int8_t rpm);

/**
 * @brief 角度輸出陣列更新函式
 * 
 * @param Channel 設定角度之腳位1(PB1)~7(PB7)
 * @param PulseWidth 指定通道的新波寬值，0~N為0 N~deg_PWM_DIV為1
 * @return uint8_t 錯誤代碼：
 */
uint8_t deg_WidthAdjust(uint8_t Channel, uint8_t PulseWidth);

/**
 * @brief 速度輸出陣列更新函式
 * 
 * @param Channel 設定輸出速度之腳位4(PD4)~7(PD7)
 * @param PulseWidth 指定通道的新波寬值，0~N為0 N~spd_PWM_DIV為1
 * @return uint8_t 錯誤代碼：
 */
uint8_t spd_WidthAdjust(uint8_t Channel, uint8_t PulseWidth);

/**
 * @brief 角度輸出陣列顯示函式
 * 
 */
void deg_PWMTable_Print();

/**
 * @brief 速度輸出陣列顯示函式
 * 
 */
void spd_PWMTable_Print();
