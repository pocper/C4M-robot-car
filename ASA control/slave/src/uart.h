#include <avr\io.h>
#include <avr\interrupt.h>

// USART Initial
void USART_Init( unsigned int baud );
// USART Transmit
void USART_Transmit( unsigned char data );
void USART0_Transmit_IntToASCII(int num);