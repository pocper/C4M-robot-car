#include "USART.h"
#include <avr/io.h>
#define F_CPU 8000000UL

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

void UART0_buf_trm(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}