#include "USART.h"

#include "pwm_def.h"

void UART0_init()
{
    //設定UART通訊鮑率
    uint16_t baud = F_CPU / 16 / UART0BAUD - 1;
    UBRR0H = (unsigned char)(baud >> 8);
    UBRR0L = (unsigned char)baud;

    //設定RX/TX 中斷 - RX 致能
    UCSR0B |= (1 << RXCIE0);

    //設定RX/TX 致能
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void UART1_init()
{
    //設定UART通訊鮑率
    uint16_t baud = F_CPU / 16 / UART1BAUD - 1;
    UBRR1H = (unsigned char)(baud >> 8);
    UBRR1L = (unsigned char)baud;

    //設定RX/TX 中斷 - RX 致能 | TX 致能
    UCSR1B |= (1 << RXCIE1) | (1 << TXCIE1);

    //設定RX/TX 致能
    UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
}

void UART0_buf_trm(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;

    DELAY(WAITTICK);
}

void UART1_buf_trm(uint8_t data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
    // DELAY(WAITTICK);
}

void UART1_trm(uint8_t RegAdd, uint8_t Bytes, uint8_t SingleDataSize, void *Data_p)
{
    uint8_t *data_p = Data_p;
    UART1_buf_trm(M2S_HEADER);
    UART1_buf_trm(RegAdd);
    UART1_buf_trm(Bytes);
    UART1_buf_trm(SingleDataSize);

    uint8_t dataCount = Bytes / SingleDataSize;
    for (int dataNum = 0; dataNum < dataCount; dataNum++)
    {
        //先送高位元組 -> 由高到低
        for (int Byte = 0; Byte < SingleDataSize; Byte++)
        {
            UART1_buf_trm(data_p[dataNum * SingleDataSize + (SingleDataSize - Byte - 1)]);
        }
    }

    UART1_buf_trm(M2S_ENDING);
}