#include "hardware.h"
#include "PCA9685.h"
#include "USART.h"

#include "src/bits_op.h"
#include "src/isr.h"
#include <avr/eeprom.h>

/* ==================== Variable Address ==================== */
uint8_t *RegAdd_Address[RegAdd_num];
uint8_t RegAdd_Size[RegAdd_num];

/* ===================== [ADC] Variable ===================== */
uint16_t Servo_Volt_ADC_Value[servo_num] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t ADG794_S1234A_ADCtoServoNumIdx[8] = {8, 10, 6, 4, 2, 0, 12, 14};
const uint8_t ADG794_S1234B_ADCtoServoNumIdx[8] = {9, 11, 7, 5, 3, 1, 13, 15};

uint8_t side = 0;
uint8_t channel = 0;
uint8_t ADC_convert_time = 0;

/* ==================== [Servo] Variable ==================== */
uint8_t UartSlaveCardID = 128;
uint16_t Servo_Value[servo_num] = {205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205};
uint16_t Servo_ActualOutputValue[servo_num] = {205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205};
uint16_t Servo_Value_MinLimit[servo_num];
uint16_t Servo_Value_MaxLimit[servo_num];
uint16_t Servo_Channel_Enable = 0;
uint8_t Servo_PowerRelaySwitch = 0;
uint16_t Servo_CurrentProtectEnable = 0xffff;
uint16_t Servo_CurrentProtectValue[servo_num];

/* ================== [USART0_RX] Variable ================== */
uint8_t Header, UartID, RegAdd, Bytes;
uint8_t uint8_data[2 * servo_num];

/* ==================== [EEPROM] Variable ==================== */
// uint8_t *EEPROM_RegAdd_Address[EEPROM_RegAdd_num];
uint8_t EEPROM_RegAdd[EEPROM_RegAdd_num] = {0, 2, 3, 8};
uint16_t EEPROM_Address[EEPROM_RegAdd_num] = {EEPROM_ADDRESS_OFFSET_UARTID, EEPROM_ADDRESS_OFFSET_MINLIMIT, EEPROM_ADDRESS_OFFSET_MAXLIMIT, EEPROM_ADDRESS_OFFSET_CURRENTPROTECT};
uint8_t EEPROM_updated = 0;
uint8_t EEPROM_updated_RegAdd_Idx = 0;

ISR(ADC_vect)
{
    uint8_t temp_ADCL = ADCL;
    uint8_t temp_ADCH = ADCH;

    // side0 =  S1234A | side1 =  S1234B
    if (side == 0)
        Servo_Volt_ADC_Value[ADG794_S1234A_ADCtoServoNumIdx[channel]] = (temp_ADCH << 8) + temp_ADCL;
    else
        Servo_Volt_ADC_Value[ADG794_S1234B_ADCtoServoNumIdx[channel]] = (temp_ADCH << 8) + temp_ADCL;
}

ISR(USART0_RX_vect)
{
    // Write Status
    // State  0 | Master -> Slave  | In Header
    // State  1 | Master -> Slave  | In UartID
    // State  2 | Master -> Slave  | In RegAdd
    // State  3 | Master -> Slave  | In Bytes
    // State  4 | Master -> Slave  | In Data
    // State  5 | Master -> Slave  | In Checksum
    // State    | Slave  -> Master | In Header
    // State    | Slave  -> Master | In Response
    // State    | Slave  -> Master | In Checksum

    // Read Status
    // State  0 | Master -> Slave  | In Header
    // State  1 | Master -> Slave  | In UartID
    // State  2 | Master -> Slave  | In RegAdd
    // State  3 | Master -> Slave  | In Bytes
    // State  5 | Master -> Slave  | In Checksum
    // State  6 | Slave  -> Master | In Header
    // State    | Slave  -> Master | In Response
    //          | Slave  -> Master | In Data
    //          | Slave  -> Master | In Checksum

    static uint8_t state = 0;
    static uint8_t chkSum = 0;
    static uint8_t data_SaveNum = 0;
    uint8_t data = UDR0;
    if (state == 0)
    {
        Header = data;
        chkSum = Header;

        if (data == ASAUART_CMD_HEADER)
            state = 1;
        else
            state = 0;
    }
    else if (state == 1)
    {
        UartID = data;
        chkSum += UartID;

        if (UartID == UartSlaveCardID)
            state = 2;
        else
            state = 0;
    }
    else if (state == 2)
    {
        RegAdd = data;
        chkSum += RegAdd;

        if ((RegAdd & 0x7f) < RegAdd_num)
            state = 3;
        else
            state = 0;
    }
    else if (state == 3)
    {
        Bytes = data;
        chkSum += Bytes;
        data_SaveNum = 0;

        if (RegAdd & 0x80) // Write register mode
            state = 4;
        else // Read register mode
            state = 6;

        if (Bytes == 0)
            state = 0;
    }
    else if (state == 4)
    {
        uint8_data[data_SaveNum] = data;
        chkSum += uint8_data[data_SaveNum];
        data_SaveNum++;
        if (data_SaveNum == Bytes)
            state = 5;
        else if (data_SaveNum > Bytes)
            state = 0;
    }
    else if (state == 5)
    {
        if (chkSum == data)
        {
            UART0_buf_trm(ASAUART_CMD_HEADER);
            UART0_buf_trm(ASAUART_RSP_OK);
            UART0_buf_trm(chkSum);

            for (int idx = 0; idx < Bytes; idx++)
                (RegAdd_Address[(RegAdd & 0x7f)])[idx] = uint8_data[idx];

            for (int i = 0; i < EEPROM_RegAdd_num; i++)
            {
                if ((RegAdd & 0x7f) == EEPROM_RegAdd[i])
                {
                    EEPROM_updated = 1;
                    EEPROM_updated_RegAdd_Idx = i;
                    break;
                }
            }
        }

        state = 0;
    }
    else if (state == 6)
    {
        if (chkSum == data)
        {
            UART0_buf_trm(ASAUART_CMD_HEADER);
            UART0_buf_trm(ASAUART_RSP_OK);

            for (int idx = 0; idx < Bytes; idx++)
            {
                UART0_buf_trm((RegAdd_Address[RegAdd & 0x7f])[idx]);
                chkSum += (RegAdd_Address[RegAdd & 0x7f])[idx];
            }

            UART0_buf_trm(chkSum);
        }

        state = 0;
    }
}

void RegAdd_init()
{
    RegAdd_Address[0] = (uint8_t *)&UartSlaveCardID;
    RegAdd_Address[1] = (uint8_t *)&Servo_Value;
    RegAdd_Address[2] = (uint8_t *)&Servo_Value_MinLimit;
    RegAdd_Address[3] = (uint8_t *)&Servo_Value_MaxLimit;
    RegAdd_Address[4] = (uint8_t *)&Servo_Channel_Enable;
    RegAdd_Address[5] = (uint8_t *)&Servo_PowerRelaySwitch;
    RegAdd_Address[6] = (uint8_t *)&Servo_CurrentProtectEnable;
    RegAdd_Address[7] = (uint8_t *)&Servo_Volt_ADC_Value;
    RegAdd_Address[8] = (uint8_t *)&Servo_CurrentProtectValue;

    RegAdd_Size[0] = sizeof(UartSlaveCardID);
    RegAdd_Size[1] = sizeof(Servo_Value);
    RegAdd_Size[2] = sizeof(Servo_Value_MinLimit);
    RegAdd_Size[3] = sizeof(Servo_Value_MaxLimit);
    RegAdd_Size[4] = sizeof(Servo_Channel_Enable);
    RegAdd_Size[5] = sizeof(Servo_PowerRelaySwitch);
    RegAdd_Size[6] = sizeof(Servo_CurrentProtectEnable);
    RegAdd_Size[7] = sizeof(Servo_Volt_ADC_Value);
    RegAdd_Size[8] = sizeof(Servo_CurrentProtectValue);
}

void PCA9685_init()
{
    PCA9685_Init(0, 50);

    for (int i = 0; i < servo_num; i++)
        PCA9685_ServoSet(i, Servo_ActualOutputValue[i]);

    SETBIT(DDRB, 0);
    CLRBIT(PORTB, 0); // PCA9685 Servo Output Enable
}

void PCA9685_update()
{
    static uint8_t isPWMStopped = 0;

    if (Servo_PowerRelaySwitch == 1)
    {
        isPWMStopped = 0;
        // 依上下限設定及禁致能狀態更新伺服機真實輸出值
        for (int i = 0; i < servo_num; i++)
        {
            if (Servo_Value[i] < Servo_Value_MinLimit[i])
                Servo_ActualOutputValue[i] = Servo_Value_MinLimit[i] + MIN_POSITION;
            else if (Servo_Value[i] > Servo_Value_MaxLimit[i])
                Servo_ActualOutputValue[i] = Servo_Value_MaxLimit[i] + MIN_POSITION;
            else
                Servo_ActualOutputValue[i] = Servo_Value[i] + MIN_POSITION;

            if (CHKBIT(Servo_Channel_Enable, i) == 0)
                Servo_ActualOutputValue[i] = 0;
        }

        for (int i = 0; i < servo_num; i++)
            PCA9685_Set(i, Servo_ActualOutputValue[i]);
    }
    else if (Servo_PowerRelaySwitch == 0 && isPWMStopped == 0)
    {
        for (int i = 0; i < servo_num; i++)
            PCA9685_Set(i, 0);

        for (int i = 0; i < 2 * servo_num; i++)
        {
            UART0_buf_trm(((uint8_t *)&Servo_Value)[i]);
            _delay_ms(1);
        }
        _delay_ms(100);

        for (int i = 0; i < 2 * servo_num; i++)
        {
            UART0_buf_trm(((uint8_t *)&Servo_ActualOutputValue)[i]);
            _delay_ms(1);
        }

        isPWMStopped = 1;
    }
}

void PowerRelay_init()
{
    SETBIT(DDRD, 7);
}

void PowerRelay_update()
{
    // 依命令控制伺服機電源總開關
    if (Servo_PowerRelaySwitch == 0)
        SETBIT(PORTD, 7); // Set High: Close Power to Servo by Relay
    else if (Servo_PowerRelaySwitch == 1)
        CLRBIT(PORTD, 7); // Set Low: Open Power to Servo by Relay
}

void DCPlugInDetect_init()
{
    CLRBIT(DDRB, 1); // 設定輸入以偵測外接DC電供是否插入
}

void DCPlugInDetect_update()
{
    // 外接DC電供偵測功能
    if (CHKBIT(DDRB, 1) == 0)
    {
        // 若偵測外接DC電供未插入時 | PINB = 0
        // 若偵測外接DC電供有插入時 | PINB = 1
        if (CHKBIT(PINB, 1) == 1)
            Servo_PowerRelaySwitch = 0; // Set High: 強制關閉伺服機總電源供應，以確保只對電池充電
    }
}

void ADC_init()
{
    ADMUX = (1 << REFS1) | (1 << REFS0) | // 內部參考電壓1.1V
            (0 << ADLAR) |                // ADC資料向右對齊
            (0 << MUX0);                  // ADC0 輸入

    ADCSRA = (1 << ADEN) |                               // ADC Enable
             (1 << ADSC) |                               // ADC Start Conversion
             (1 << ADIE) |                               // ADC Interrupt Enable
             (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // ADC freq = freq_osc /64
}

void ADG794_init()
{
    SETBIT(DDRD, 5); // set DDRD5 OUTPUT | MuxEnable
    SETBIT(DDRD, 6); // set DDRD6 OUTPUT | MuxSwitch

    CLRBIT(PORTD, 5); // EN = 0
    CLRBIT(PORTD, 6); // IN = 0

    ADC_init();
}

void ADC_update()
{
    // Check ADC conversion completes
    if (ADCSRA & (1 << ADSC))
        return;

    // 一個通道轉換三次 -> 求多次結果
    if (ADC_convert_time < ADC_SING_CHAN_CONVERT_TIMES - 1)
    {
        ADC_convert_time++;
    }
    else
    {
        channel++;
        ADC_convert_time = 0;
    }

    if (channel > 7)
    {
        channel = 0;

        if (side == 0)
        {
            SETBIT(PORTD, 6); // IN = 1
            side = 1;
        }
        else
        {
            CLRBIT(PORTD, 6); // IN = 0
            side = 0;
        }
    }

    ADMUX = (ADMUX & 0xf0) | (channel << MUX0);
    ADCSRA |= (1 << ADSC); // ADC Start Conversion
}

void CurrentProtect_update()
{
    // Voltage  -> ADC tick
    // 0.0   [V]  ->    0
    // 1.1   [V]  -> 1024
    //
    // --------------------
    // 0.001 [V]  <-    1
    //
    // --------------------
    // Test - Internal VCC [1.1V]
    // 1.013 [V]  <- 1013
    //
    // --------------------
    // Mesurement on Voltage
    //               Voltage  -> ADC tick
    // Usually  -> 0.023 [V]  ->   23
    // Power on -> 0.056 [V]  ->   56

    // Mesurement on Current
    //               Current  -> ADC tick
    // Usually  ->  0.0 [mA]  ->  0  -- check
    // Power on -> 17.4 [mA]  ->  4  -- check
    //
    // --------------------
    // Normal ADC tick
    // 0x03 ~ 0x19
    // --------------------
    // ERROR ADC tick
    // IDX - Val[HEX]   -  Val[DEC]   -  Voltage[V]
    // 01  -  0xFD      -    253      -    0.2717
    // 02  -  0xF3      -    243      -    0.2610
    // 03  -  0x86      -    134      -    0.1439
    // 04  -  0xD8      -    216      -    0.2320
    // 05  -  0xE6      -    230      -    0.2470
    // 06  -  0xFE      -    254      -    0.2728
    // 07  -  0xA5      -    165      -    0.1772
    // 08  -  0xE2      -    226      -    0.2242
    // 09  -  0xF6      -    246      -    0.2642
    // 10  -  0xDA      -    218      -    0.2341
    // 11  -  0x103     -    259      -    0.2782
    // 12  -  0x104     -    260      -    0.2792
    // 13  -  0x105     -    261      -    0.2803
    //
    // --------------------
    // Servo_Volt_ADC_Value = 256 | 施加阻力馬上停止運轉
    // Servo_Volt_ADC_Value = 300 | 施加阻力並額外施加逆向阻力則停止運轉
    //
    // --------------------
    if (Servo_CurrentProtectEnable)
    {
        for (int i = 0; i < servo_num; i++)
            if (CHKBIT(Servo_CurrentProtectEnable, i) == 1 &&
                Servo_Volt_ADC_Value[i] > Servo_CurrentProtectValue[i])
                CLRBIT(Servo_Channel_Enable, i);
    }
}

void ADC_value_printf()
{
    for (int i = 0; i < servo_num; i++)
        for (int j = 0; j < sizeof(uint16_t); j++)
            UART0_buf_trm(((uint8_t *)(&Servo_Volt_ADC_Value[i]))[j]);
}

// void EEPROM_init()
// {
//     EEPROM_RegAdd_Address[0] = (uint8_t *)&EEPROM_UartSlaveCardID;
//     EEPROM_RegAdd_Address[1] = (uint8_t *)&EEPROM_Servo_Value_MinLimit;
//     EEPROM_RegAdd_Address[2] = (uint8_t *)&EEPROM_Servo_Value_MaxLimit;
//     EEPROM_RegAdd_Address[3] = (uint8_t *)&EEPROM_Servo_CurrentProtectValue;
// }

// void EEPROM_Flash()
// {
//     for (int i = 0; i < EEPROM_RegAdd_num; i++)
//         eeprom_update_block(EEPROM_RegAdd_Address[i], (uint8_t *)EEPROM_Address[i], RegAdd_Size[EEPROM_RegAdd[i]]);
// }

void EEPROM_read()
{
    for (int i = 0; i < EEPROM_RegAdd_num; i++)
        eeprom_read_block(RegAdd_Address[EEPROM_RegAdd[i]], (uint8_t *)EEPROM_Address[i], RegAdd_Size[EEPROM_RegAdd[i]]);
}

void tmp_EEPROM_read()
{
    UartSlaveCardID = 128;

    uint16_t EEPROM_Servo_Value_MinLimit[servo_num] = {72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72};
    uint16_t EEPROM_Servo_Value_MaxLimit[servo_num] = {338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338, 338};
    uint16_t EEPROM_Servo_CurrentProtectValue[servo_num] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400};

    for (int i = 0; i < servo_num; i++)
    {
        Servo_Value_MinLimit[i] = EEPROM_Servo_Value_MinLimit[i];
        Servo_Value_MaxLimit[i] = EEPROM_Servo_Value_MaxLimit[i];
        Servo_CurrentProtectValue[i] = EEPROM_Servo_CurrentProtectValue[i];
    }
}

void EEPROM_update()
{
    if (EEPROM_updated)
    {
        eeprom_update_block(RegAdd_Address[EEPROM_RegAdd[EEPROM_updated_RegAdd_Idx]],
                            (uint8_t *)EEPROM_Address[EEPROM_updated_RegAdd_Idx],
                            RegAdd_Size[EEPROM_RegAdd[EEPROM_updated_RegAdd_Idx]]);
        EEPROM_updated = 0;
    }
}

void EEPROM_read_printf()
{
    uint8_t uint8_data;
    uint16_t uint16_data[servo_num];

    // UartSlaveCardID
    eeprom_read_block((void *)&uint8_data, (uint8_t *)EEPROM_Address[0], RegAdd_Size[EEPROM_RegAdd[0]]);
    UART0_buf_trm(uint8_data);

    // Servo_Value_MinLimit
    eeprom_read_block((void *)&uint16_data, (uint8_t *)EEPROM_Address[1], RegAdd_Size[EEPROM_RegAdd[1]]);
    for (int i = 0; i < servo_num; i++)
        for (int j = 0; j < sizeof(int16_t); j++)
            UART0_buf_trm(*(((uint8_t *)&uint16_data[0]) + sizeof(int16_t) * i + j));

    // Servo_Value_MaxLimit
    eeprom_read_block((void *)&uint16_data, (uint8_t *)EEPROM_Address[2], RegAdd_Size[EEPROM_RegAdd[2]]);
    for (int i = 0; i < servo_num; i++)
        for (int j = 0; j < sizeof(int16_t); j++)
            UART0_buf_trm(*(((uint8_t *)&uint16_data[0]) + sizeof(int16_t) * i + j));

    // Servo_CurrentProtectValue
    eeprom_read_block((void *)&uint16_data, (uint8_t *)EEPROM_Address[3], RegAdd_Size[EEPROM_RegAdd[3]]);
    for (int i = 0; i < servo_num; i++)
        for (int j = 0; j < sizeof(int16_t); j++)
            UART0_buf_trm(*(((uint8_t *)&uint16_data[0]) + sizeof(int16_t) * i + j));
}
