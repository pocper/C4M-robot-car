#include "i2c.h"

#include <avr/iom328pb.h>

static unsigned char masterMode;

// i2c Init
void i2c_Init(void)
{
    TWSR1 &= ~((1 << TWPS1) | (1 << TWPS0)); // pre-scalar 1
    TWBR1 = ((F_CPU / F_I2C) - 16) / 2;      // baud rate factor 12
}

unsigned char i2c_TX_Start(unsigned char Mode)
{
    char status = 0;
    masterMode = Mode; // set global state of R/W bit

    /* clear interrupt flag, issue start command (gain control of bus as
       master), enable I2C (SCL and SDA are automatically reconfigured) */
    TWCR1 |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* wait until start transmitted */
    while (!(TWCR1 & (1 << TWINT)))
        ;

    switch (TWSR1 & 0xF8)
    {
    /* start condition sent from master */
    case 0x08:
        status = TRANSMISSION_SUCCESS;
        break;

    /* repeat start condition sent from master */
    case 0x10:
        status = TRANSMISSION_SUCCESS;
        break;

    default:
        status = TRANSMISSION_ERROR;
        break;
    }

    return status;
}

unsigned char i2c_TX_Address(unsigned char Address)
{
    char status = 0;

    TWDR1 = (Address << 1) | masterMode;
    /* clear start command to release bus as master */
    TWCR1 &= ~(1 << TWSTA);
    /* clear interrupt flag */
    TWCR1 |= (1 << TWINT);

    /* wait until address transmitted */
    while (!(TWCR1 & (1 << TWINT)))
        ;

    if (masterMode == MASTER_TRANSMITTER)
    {
        switch (TWSR1 & 0xF8)
        {
        /* address|write sent and ACK returned */
        case 0x18:
            status = TRANSMISSION_SUCCESS;
            break;

        /* address|write sent and NACK returned slave */
        case 0x20:
            status = TRANSMISSION_ERROR;
            break;

        /* address|write sent and bus failure detected */
        case 0x38:
            status = TRANSMISSION_ERROR;
            break;

        default:
            status = TRANSMISSION_ERROR;
            break;
        }
    }
    else if (masterMode == MASTER_RECEIVER)
    {
        switch (TWSR1 & 0xF8)
        {
        /* address|read sent and ACK returned */
        case 0x40:
            status = TRANSMISSION_SUCCESS;
            break;

        /* address|read sent and NACK returned */
        case 0x48:
            status = TRANSMISSION_ERROR;
            break;

        case 0x38:
            status = TRANSMISSION_ERROR;
            break;

        default:
            status = TRANSMISSION_ERROR;
            break;
        }
    }

    return status;
}

unsigned char i2c_TX_Byte(unsigned char ByteData)
{
    char status = 0;
    TWDR1 = ByteData;      // load data buffer with data to be transmitted
    TWCR1 |= (1 << TWINT); // clear interrupt flag

    /* wait until data transmitted */
    while (!(TWCR1 & (1 << TWINT)))
        ;

    /* retrieve transmission status codes */
    switch (TWSR1 & 0xF8)
    {
    /* byte sent and ACK returned */
    case 0x28:
        status = TRANSMISSION_SUCCESS;
        break;

    /* byte sent and NACK returned */
    case 0x30:
        status = TRANSMISSION_ERROR;
        break;

    /* byte sent and bus failure detected */
    case 0x38:
        status = TRANSMISSION_ERROR;
        break;

    default:
        status = TRANSMISSION_ERROR;
        break;
    }

    return status;
}

unsigned char i2c_Timeout(void)
{
    unsigned char time = TIMEOUT;
    char status = BUS_DISCONNECTED;

    while (time-- > 0)
    {
        /* check to see if bus is ready */
        if ((TWCR1 & (1 << TWINT)))
        {
            status = BUS_CONNECTED;
            break;
        }
    }

    return status;
}

unsigned char i2c_RX_Byte(unsigned char Response)
{
    char status;

    if (Response == ACK)
    {
        TWCR1 |= (1 << TWEA); // generate ACK
    }
    else
    {
        TWCR1 &= ~(1 << TWEA); // generate NACK
    }

    /* clear interrupt flag */
    TWCR1 |= (1 << TWINT);

    /* detect bus time-out */
    if (i2c_Timeout() != BUS_DISCONNECTED)
    {
        /* retrieve transmission status codes or received data */
        switch (TWSR1 & 0xF8)
        {
        /* data byte read and ACK returned by master */
        case 0x50:
            status = TWDR1;
            break;

        /* data byte read and NACK returned by master */
        case 0x58:
            status = TWDR1;
            break;

        /* bus failure detected */
        case 0x38:
            status = TRANSMISSION_ERROR;
            break;

        default:
            status = TRANSMISSION_ERROR;
            break;
        }
    }
    else
    {
        status = TRANSMISSION_ERROR;
    }

    return status;
}

void i2c_TX_Stop(void)
{
    /* clear interrupt flag, issue stop command (cleared automatically) */
    TWCR1 |= (1 << TWINT) | (1 << TWSTO);

    while (!(TWCR1 & (1 << TWSTO)))
        ; // wait until stop transmitted
}
