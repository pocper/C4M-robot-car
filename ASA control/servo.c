#include "servo.h"

#define deg_MAXINDEX deg_PWM_DIV - 1
#define spd_MAXINDEX spd_PWM_DIV - 1

#define BASICHI 1
#define HI2LOW 2
#define LOW2END 3
#define BIT(m) (0x01 << (m))
#define BIT_CLEAR(p, m) ((p) &= ~(BIT(m)))
#define BIT_SET(p, m) ((p) |= (BIT(m)))
#define BIT_PUT(c, p, m) \
    (c ? BIT_SET(p, m) : BIT_CLEAR(p, m))     //將c蓋寫變數p的第m位元。
#define BIT_GET(p, m) (((p) & (BIT(m))) >> m) //取得變數p的第m位元的值。

my_PWMStr_t deg_PWM_str;
PWMStr_t spd_PWM_str;
Task task;
extern char receiveData[maxReceieveBuffer];

ISR(TIMER1_COMPA_vect)
{
    static uint8_t Index = 0, state = 1;
    switch (state)
    {
    case BASICHI:
        //除頻值8
        TCCR1B = (TCCR1B & ~(0x07)) | 0x02;
        OCR1A = 685;
        //時間:0.5007ms
        // TCCR1B = (TCCR1B & ~(0x07)) | 0x03;
        // OCR1A = 146;
        PORTB = deg_PWM_str.PWM_BASICHI;
        state = 2;
        break;

    case HI2LOW:
        OCR1A = 13;
        //時間：2.016ms
        // OCR1A = 2;
        PORTB = deg_PWM_str.PWMTableB[Index];
        if (Index == deg_MAXINDEX)
        {
            Index = 0;
            state = 3;
        }
        Index++;
        break;

    case LOW2END:
        //除頻值1024
        TCCR1B = (TCCR1B & ~(0x07)) | 0x05;
        OCR1A = 195;
        //時間：17.49ms
        PORTB = 0x00;
        state = 1;
        break;
    }
}

ISR(TIMER3_COMPA_vect)
{
    static uint8_t Index = 0, state = 1;
    switch (state)
    {
    case BASICHI:
        //除頻值8
        TCCR3B = (TCCR3B & ~(0x07)) | 0x03;
        OCR3A = 146;
        PORTD = spd_PWM_str.PWM_BASICHI;
        state = 2;
        break;

    case HI2LOW:
        OCR3A = 2;
        PORTD = spd_PWM_str.PWMTableB[Index];
        if (Index == spd_MAXINDEX)
        {
            Index = 0;
            state = 3;
        }
        Index++;
        break;

    case LOW2END:
        TCCR3B = (TCCR3B & ~(0x07)) | 0x05;
        OCR3A = 192;
        PORTD = 0x00;
        state = 1;
        break;
    }
}

ISR(TIMER2_COMP_vect)
{
    for (int i = 0; i < CH_num; i++)
    {
        if (task.counter[i] < task.Target[i] + 1)
        {
            task.counter[i]++;
        }

        if (task.counter[i] == task.Target[i])
        {
            if (i == 0)
            {
                Servo_Speed_set(4, 0);
                Servo_Speed_set(5, 0);
                Servo_Speed_set(6, 0);
                Servo_Speed_set(7, 0);
            }

            if (i == 1)
            {
                Servo_Degree_set(1, Servo_STOP);
                Servo_Degree_set(2, Servo_STOP);
            }

            if (i == 2)
            {
                for (int j = 3; j < 8; j++)
                    Servo_Degree_set(j, Servo_STOP);
            }
        }
    }
}

void timer0_init()
{
    REGFPT(&TCCR0, 0x08, 3, 1); /*CTC*/
    REGFPT(&TCCR0, 0x07, 0, 7); /*除頻1024*/

    OCR0 = 107;
    //時間：0.01s
    // DDRD = (DDRD & (~(0xf0))) | 0x00;
    REGFPT(&TIMSK, 0x02, 1, 1); /*致能中斷*/
}

void timer1_init()
{
    REGFPT(&TCCR1A, 0x03, 0, 0); /*CTC*/
    REGFPT(&TCCR1B, 0x18, 3, 1); /*CTC*/
    REGFPT(&TCCR1B, 0x07, 0, 2); /*除頻8*/
    REGFPT(&TIMSK, 0x10, 4, 1);  /*致能中斷*/
    OCR1A = 100;
    DDRB = 0xff;
}

void timer3_init()
{
    REGFPT(&TCCR3A, 0x03, 0, 0); /*CTC*/
    REGFPT(&TCCR3B, 0x18, 3, 1); /*CTC*/
    REGFPT(&TCCR3B, 0x07, 0, 1); /*除頻8*/
    REGFPT(&ETIMSK, 0x10, 4, 1); /*致能中斷*/
    OCR3A = 100;
    DDRD = (DDRD & (~(0xf0))) | 0xf0;
}

void timer2_init()
{
    REGFPT(&TCCR2, 0x48, 3, 1); /*CTC*/
    REGFPT(&TCCR2, 0x07, 0, 5); /*除頻1024*/
    REGFPT(&TIMSK, 0x80, 7, 1); /*致能中斷*/
    OCR2 = 107;
    //時間：0.01s

    Task_init();
}

void Task_init()
{
    //ERROR timer3與timer2的中斷不會同時開始
    //timer2不一定會真的計時到1秒鐘
    //車輪
    task.Target[0] = 100;                 //無限轉1.0秒關閉
    task.counter[0] = task.Target[0] + 1; //初始化

    //車斗
    task.Target[1] = 50;                  //有限角0.5秒關閉
    task.counter[1] = task.Target[1] + 1; //初始化

    //手臂
    task.Target[2] = 50;                  //有限角0.5秒關閉
    task.counter[2] = task.Target[2] + 1; //初始化
}

uint8_t Servo_Degree_set(uint8_t channel, int8_t Degree)
{
    uint8_t PulseWidth = Degree2Width(Degree);

    // if (PulseWidth == 255)
    //     return 1;

    if (channel > 7)
        return 2;

    if (Degree > 90 || Degree < -90)
    {
        PulseWidth = 0;
        BIT_PUT(0, deg_PWM_str.PWM_BASICHI, channel);
    }
    else
    {
        BIT_PUT(1, deg_PWM_str.PWM_BASICHI, channel);
    }

    deg_WidthAdjust(channel, PulseWidth);
    return 0; // Set successfully
}

uint8_t Servo_Speed_set(uint8_t channel, int8_t speed)
{
    uint8_t PulseWidth = RPM2Width(speed);
    if (PulseWidth == 255)
        return 1; // Error: speed outpace

    if (channel < 4 || channel > 7)
        return 2; // Error:Channel outpace

    if (speed == 0)
    {
        PulseWidth = 0;
        BIT_PUT(0, spd_PWM_str.PWM_BASICHI, channel);
    }
    else
    {
        BIT_PUT(1, spd_PWM_str.PWM_BASICHI, channel);
    }
    spd_WidthAdjust(channel, PulseWidth);
    return 0; // Set successfully
}

uint8_t Degree2Width(int8_t Degree)
{
    /*
    順時針是正方向
    0.5ms -> -112.5[Deg]
    0.7ms ->  -90.0[Deg]
    1.5ms ->    0.0[Deg]
    2.3ms ->  +90.0[Deg]
    2.5ms -> +112.5[Deg]
    -----------------
    0.5000ms ->   0等分
    2.5000ms -> 200等分
    -----------------
    0.0100ms <-   1等分
    */
    if (Degree > 90 || Degree < -90)
        return 255;

    float pwm = (2.5 - 0.5) * ((float)Degree - (-112.5)) / 225; //單位[ms]
    // printf("PWM = %f, split = %d\n", pwm + 0.5, (uint8_t)(pwm / 0.01));
    return pwm / 0.01;
}

uint8_t RPM2Width(int8_t rpm)
{
    if (rpm > 58 || rpm < -58)
        return 255;

    uint8_t pwm = 0;
    if (rpm <= 58 && rpm >= 48)
    {
        pwm = 17.745 * rpm - 801 + 0.5;
        if (pwm >= 69)
        {
            pwm = 75;
        }
    }
    if (rpm <= 47 && rpm >= 0)
    {
        pwm = 0.26 * rpm + 38 + 0.5;
    }
    if (rpm <= -1 && rpm >= -47)
    {
        pwm = 0.26 * rpm + 38 + 0.5;
    }
    if (rpm <= -48 && rpm >= -58)
    {
        int ans = 17.745 * rpm + 845;
        if (ans < 0)
        {
            rpm = 0;
        }
        else
        {
            rpm = ans;
        }
    }
    return pwm;
}

uint8_t deg_WidthAdjust(uint8_t Channel, uint8_t PulseWidth)
{
    if (Channel > 7)
        return 1; // Error: channel outpace

    if (PulseWidth > deg_PWM_DIV)
        return 2; // Error: PulseWidth outpace

    for (int i = 0; i < PulseWidth; i++)
    {
        BIT_PUT(1, deg_PWM_str.PWMTableB[i], Channel);
    }
    for (int j = PulseWidth; j < deg_PWM_DIV; j++)
    {
        BIT_PUT(0, deg_PWM_str.PWMTableB[j], Channel);
    }

    return 0;
}

uint8_t spd_WidthAdjust(uint8_t Channel, uint8_t PulseWidth)
{
    if (Channel > 7)
        return 1; // Error: channel outpace

    if (PulseWidth > spd_PWM_DIV)
        return 2; // Error: PulseWidth outpace

    for (int i = 0; i < PulseWidth; i++)
    {
        BIT_PUT(1, spd_PWM_str.PWMTableB[i], Channel);
    }
    for (int j = PulseWidth; j < spd_PWM_DIV; j++)
    {
        BIT_PUT(0, spd_PWM_str.PWMTableB[j], Channel);
    }

    return 0;
}

void deg_PWMTable_Print()
{
    for (int i = 4; i < 5; i++)
    {
        printf("i=%d\n", i);
        for (int j = 0; j < deg_PWM_DIV; j++)
        {
            printf("%d ", BIT_GET(deg_PWM_str.PWMTableB[j], i));
        }
        printf("\n");
    }
}

void spd_PWMTable_Print()
{
    for (int i = 4; i < 8; i++)
    {
        printf("i=%d\n", i);
        for (int j = 0; j < spd_PWM_DIV; j++)
        {
            printf("%d ", BIT_GET(spd_PWM_str.PWMTableB[j], i));
        }
        printf("\n");
    }
}