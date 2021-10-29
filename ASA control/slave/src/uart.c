#include "uart.h"

// Basic function define:
#define	CheckBit(data,bit) ((data & (1<<bit))==(1<<bit))
#define	ClearBit(data,bit) (data &= ~(1<<bit))
#define	SetBit(data,bit)   (data |= (1<<bit))

// USART Initial
void USART_Init( unsigned int baud )
{
	//baud = 11059200/16/baud-1;
	baud = 8000000/16/baud-1;
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

// USART Transmit
void USART_Transmit( unsigned char data )
{
	while ( !( UCSR0A & (1<<UDRE0)) ) ;
	UDR0 = data;
}

void USART0_Transmit_IntToASCII(int num)
{
	int i;
	char num_char[5] = {' ',' ',' ',' ',' '};
	if(num<0) USART_Transmit( '-' );	
	if(num==0)
	num_char[0] = '0';
	else
	for(i=0; i<5; i++)
	{
		if(num>0)
		{
			num_char[i] = num%10+0x30;
			num /= 10;
		}
		if(num<0)
		{
			num_char[i] = (num%10)-(num%10)*2+0x30;
			num /= 10;
		}
	}

	for(i=4; i>=0; i--)
	USART_Transmit( num_char[i] );
}
/*
char RelaySwitch;
int ServoChannel;
int ServoValue;
ISR(USART0_RX_vect)
{
	unsigned char data;
	data = UDR0;
	if(data==0xAA)
	{
		RelaySwitch = 1;
		ClearBit(PORTD,7);
	}
		else if(data==0xBB)
		{
			RelaySwitch =0;
			SetBit(PORTD,7);
		}
		else if(data=='U')
		{
			ServoValue += 3;
			if(ServoValue>358)
			ServoValue=358;
			PCA9685_ServoSet( ServoChannel, ServoValue);
			USART0_Transmit_IntToASCII( ServoChannel );
			USART0_Transmit_IntToASCII( ServoValue );
		}
		else if(data=='D')
		{
			ServoValue -= 3;
			if(ServoValue<51)
				ServoValue=51;
			PCA9685_ServoSet( ServoChannel, ServoValue);
			USART0_Transmit_IntToASCII( ServoChannel );
			USART0_Transmit_IntToASCII( ServoValue );
		}
		else if(data=='N')
		{
			ServoChannel++;
			if(ServoChannel>=16)
				ServoChannel = 0;
			USART0_Transmit_IntToASCII( ServoChannel );
		}

	//UDR0 = data;
	USART_Transmit( data );

}
*/