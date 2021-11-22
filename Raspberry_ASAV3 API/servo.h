#include <stdio.h>
#ifndef SERVO_H
#define SERVO_H
#ifdef __cplusplus
extern "C"
{
#endif
    /**
 * @brief 車輪控制制能
 * 
 * @param fd 開啟檔案之描述，fildes
 */
    void MOTION_ENABLE(int fd);

    /**
 * @brief 讀取特定csv格式檔案函式
 * 
 * 
 * @param fd 開啟檔案之描述，fildes
 * @param fileName 檔案名稱[含副檔名]
 */
    void read_csv(int fd, char *fileName);

    /**
 * @brief UART特定字串傳輸有限轉伺服機函式
 * 
 * @param fd 開啟檔案之描述，fildes
 * @param data_p 資料指標
 */
    void arm_trm(int fd, int *data_p);
    /**
 * @brief UART特定字串傳輸無限轉伺服機函式
 * 
 * @param fd 
 * @param data_p 
 */
    void motion_trm(int fd, char data_p);

    /**
 * @brief csv讀取資料轉換函式
 * 轉換前資料範圍 : -128 ~ 128。
 * 轉換後資料範圍 :    0 ~ 255。
 * 
 * @param num csv資料
 * @return int 轉換後資料
 */
    int deg2Byte(int num);

#ifdef __cplusplus
}
#endif
#endif