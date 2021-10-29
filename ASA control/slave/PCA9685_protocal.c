#include "PCA9685_protocal.h"

uint8_t globalAddress;
uint16_t globalFrequency;

// PCA9685 Initial
void PCA9685_Init(uint8_t Address, uint16_t Frequency)
{
	globalAddress = Address;
	globalFrequency = Frequency;

	i2c_Init();

	/* Select slave device, select MODE1 register, then set AI (auto-increment)
		enable, SLEEP active, and ALLCALL enable */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40 + Address); // 0x40 adds addr MSB (fig 4 in datasheet)
	i2c_TX_Byte(0x00);				// MODE1 register
	i2c_TX_Byte(0b00110001);		// set register configuration
	i2c_TX_Stop();

	_delay_ms(1);

	/* Calculate frequency prescalar for usage below. PCA9685 contains a 25 MHz
		internal clock that can be prescaled to achieve the desired output
		frequency. The prescalar can be a number between 0xFF (24 Hz) and 0x03
		(1526 Hz). Multiply frequency by 0.92 to compensate for frequency
		inaccuracy. Declare the variable as volatile to force computation
		where written in source, otherwise compiler will place expression inline
		where it is used (during I2C transmission, causing a brief delay due to
		time it takes to compute result). Note: equation can be optimized
		without needing a float) */
	//volatile unsigned char Prescalar = (25000000 / ((float)4096 * Frequency * 0.92)) - 1;
	volatile unsigned char Prescalar = (25000000 / ((float)4096 * Frequency * 0.97)) - 1;

	/* Select slave device, select PRESCALE register, then set output driver
		frequency using prescalar */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40);
	i2c_TX_Byte(0xFE);		// PRESCALE register
	i2c_TX_Byte(Prescalar); // set register configuration
	i2c_TX_Stop();

	_delay_ms(1);

	/* Select slave device, select MODE1 register, then set AI (auto-increment)
		enable, SLEEP disable, and ALLCALL enable */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40);
	i2c_TX_Byte(0x00);		 // MODE1 register
	i2c_TX_Byte(0b10100001); // set register configuration
	i2c_TX_Stop();

	_delay_ms(1);

	/* Select slave device, select MODE2 register, then set INVRT (inverted
		output) disable, OCH (outputs change on STOP command) enable, OUTDRV
		(output driver configuration) to totem pole output and OUTNE (output not
		enable mode) to 0x00 */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40);
	i2c_TX_Byte(0x01);		 // MODE2 register
	i2c_TX_Byte(0b00000100); // set register configuration
	i2c_TX_Stop();
}

// PCA9685 Servo Position Set
void PCA9685_ServoSet(unsigned char servoNum, unsigned int Position)
{
	/* Set limits on Position */
	Position += MIN_POSITION;
	if (Position > MAX_POSITION)
		Position = MAX_POSITION;
	else if (Position < MIN_POSITION)
		Position = MIN_POSITION;
	else
		;

	/* Output turns on at 0 counts (simplest way), and will turn off according
		to calculations above. Break the 12-bit count into two 8-bit values */
	unsigned char offLowCmnd = Position;
	unsigned char offHighCmnd = Position >> 8;

	/* Each output is controlled by 2x 12-bit registers: ON to specify the count
		time to turn on the LED (a number from 0-4095), and OFF to specify the
		count time to turn off the LED (a number from 0-4095). Each 12-bit
		register is composed of 2 8-bit registers: a high and low. */

	/* Select slave device, select LEDXX_ON_L register, set contents of
		LEDXX_ON_L, then set contents of next 3 registers in sequence (only if
		auto-increment is enabled). */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40 + globalAddress);
	i2c_TX_Byte(SERVO0 + (4 * servoNum)); // select LEDXX_ON_L register
	i2c_TX_Byte(0x00);					  // set value of LEDXX_ON_L
	i2c_TX_Byte(0x00);					  // set value of LEDXX_ON_H
	i2c_TX_Byte(offLowCmnd);			  // set value of LEDXX_OFF_L
	i2c_TX_Byte(offHighCmnd);			  // set value of LEDXX_OFF_H
	i2c_TX_Stop();
}

// PCA9685 Set
void PCA9685_Set(unsigned char servoNum, unsigned int value)
{
	/* Output turns on at 0 counts (simplest way), and will turn off according
		to calculations above. Break the 12-bit count into two 8-bit values */
	unsigned char offLowCmnd = value;
	unsigned char offHighCmnd = value >> 8;

	/* Each output is controlled by 2x 12-bit registers: ON to specify the count
		time to turn on the LED (a number from 0-4095), and OFF to specify the
		count time to turn off the LED (a number from 0-4095). Each 12-bit
		register is composed of 2 8-bit registers: a high and low. */

	/* Select slave device, select LEDXX_ON_L register, set contents of
		LEDXX_ON_L, then set contents of next 3 registers in sequence (only if
		auto-increment is enabled). */
	i2c_TX_Start(MASTER_TRANSMITTER);
	i2c_TX_Address(0x40 + globalAddress);
	i2c_TX_Byte(SERVO0 + (4 * servoNum)); // select LEDXX_ON_L register
	i2c_TX_Byte(0x00);					  // set value of LEDXX_ON_L
	i2c_TX_Byte(0x00);					  // set value of LEDXX_ON_H
	i2c_TX_Byte(offLowCmnd);			  // set value of LEDXX_OFF_L
	i2c_TX_Byte(offHighCmnd);			  // set value of LEDXX_OFF_H
	i2c_TX_Stop();
}