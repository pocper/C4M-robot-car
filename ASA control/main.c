#include "c4mlib.h"
#include <string.h>

#define UARTBAUD 38400
#define maxTransmitBytes 10
#define maxReceiveBytes 5

typedef struct Wheel
{
    int left_front;  //左前輪
    int right_front; //右前輪
    int left_rear;   //左後輪
    int right_rear;  //右後輪
} Wheel;

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

Wheel wheelVal = {-1, 1, -1, 1};
PWMStr_t *global_PWM_str;

int RPM = 30;
const char init_str[] = "Success";
const char key_value[] = "WASDQEZCR";

void UART_init();
// void Timer_init();

void Movement_condition(int dir);
void Movement_update();

ISR(USART1_RX_vect)
{
    char receiveData[maxReceiveBytes];
    int str_length = 0;

    while ((UCSR1A & (1 << RXC1)) >> RXC1)
    {
        receiveData[str_length] = UDR1;
        _delay_ms(1);
        // printf("%d\n", receiveData[str_length]);
        // printf("str_length=%d\n", str_length);
        if (str_length < maxReceiveBytes - 1)
            str_length++;
        else
            break;
    }
    receiveData[str_length] = '\0';

    if (!strcmp(receiveData, "con"))
    {
        UARTM_trm(3, 9, 0, sizeof(init_str), (void *)&init_str, 5);
    }
    else
    {
        //找出接收到的資料並執行
        char *findDir = strstr(key_value, receiveData);
        if (findDir != NULL)
            Movement_condition(findDir - key_value);
    }
}

int main()
{
    C4M_DEVICE_set();
    UART_init();

    ASASERVO_PWMPREPRO_LAY();
    global_PWM_str = &PWM_str;
    sei();

    printf("Start\n");

    while (1)
    {
        ;
    }

    return 0;
}

void UART_init()
{
    //設定UART通訊包率
    uint16_t baud = F_CPU / 16 / UARTBAUD - 1;
    UBRR1H = (uint8_t)(baud >> 8);
    UBRR1L = (uint8_t)baud;

    //設定RX/TX interrupt - RX ENABLE
    UCSR1B |= (1 << RXCIE1);

    //設定RX/TX 致能
    UCSR1B |= (1 << RXEN1) | (1 << TXEN1);

    //設定傳輸資料 8 bits
    // UCSR1B &= (0 << UCSZ12);
    // UCSR1C |= (3 << UCSZ10);
}

// void Timer_init()
// {
//     //TCCR3A normal port operation
//     REGFPT(&TCCR3A, 0x03, 0, 0);

//     //TCCR3B 4:3 CTC mode
//     REGFPT(&TCCR3B, 0x18, 3, 1);

//     //TCCR3B 2:0 N = 1024
//     REGFPT(&TCCR3B, 0x07, 0, 5);

//     OCR3A = 539;
//     //f_OCR = f_clk_IO / (2 * N * (1 + OCR3))
//     //      = 11059200 / (2 * 1024 * (1 + 539)) = 10
//     //Enable Timer3 Interrupt
//     REGFPT(&ETIMSK, 0x10, 4, 1);
// }

void Movement_condition(int dir)
{
    printf("dir=%d\n", dir);
    switch (dir)
    {
    case forward:
        wheelVal.left_front = -1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = 1;
        break;

    case backward:
        wheelVal.left_front = 1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = -1;
        break;

    case left:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;

    case right:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;

    case right_front:
        wheelVal.left_front = -1;
        wheelVal.right_front = 0;
        wheelVal.left_rear = 0;
        wheelVal.right_rear = 1;
        break;

    case left_front:
        wheelVal.left_front = 0;
        wheelVal.right_front = 1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = 0;
        break;

    case right_behind:
        wheelVal.left_front = 1;
        wheelVal.right_front = 0;
        wheelVal.left_rear = 0;
        wheelVal.right_rear = -1;
        break;

    case left_behind:
        wheelVal.left_front = 0;
        wheelVal.right_front = -1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 0;
        break;

    case rotate_cw:
        wheelVal.left_front = -1;
        wheelVal.right_front = -1;
        wheelVal.left_rear = -1;
        wheelVal.right_rear = -1;
        break;

    case rotate_ccw:
        wheelVal.left_front = 1;
        wheelVal.right_front = 1;
        wheelVal.left_rear = 1;
        wheelVal.right_rear = 1;
        break;
    }

    Movement_update();
}

void Movement_update()
{
    /*
            ---front---
            ___________
    3 -     |         |   - 1
            |         |
            |         |
            |         |
            |         |   - 2
    4 -     |_________|
            ---back---
    */

    // printf("RPM = %d\n", RPM);
    // printf("left_front = %d\n", wheelVal.left_front);
    // printf("right_front = %d\n", wheelVal.right_front);
    // printf("left_rear = %d\n", wheelVal.left_rear);
    // printf("right_rear = %d\n", wheelVal.right_rear);
    // printf("\n");

    AsaServo_PwmPrePro_cmd(global_PWM_str, 1, RPM * wheelVal.right_front);
    AsaServo_PwmPrePro_cmd(global_PWM_str, 2, RPM * wheelVal.right_rear);
    AsaServo_PwmPrePro_cmd(global_PWM_str, 3, RPM * wheelVal.left_rear);
    AsaServo_PwmPrePro_cmd(global_PWM_str, 4, RPM * wheelVal.left_front);
}