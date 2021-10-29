#ifndef __PCA9685_H__
#define __PCA9685_H__

#include <avr/io.h>
#include <util/delay.h>
#include "src/i2c.h"
#include "src/uart.h"

#define SERVO0 0x06

#define MIN_POSITION	 102	// 0.5ms
#define NEUTRAL_POSITION 307	// 1.5ms
#define MAX_POSITION	 512	// 2.5ms

void PCA9685_Init(unsigned char Address, unsigned int Frequency);
// Position: 0~410 => 0.5ms~2.5ms
void PCA9685_ServoSet(unsigned char servoNum, unsigned int Position);
// PCA9685 Set
void PCA9685_Set(unsigned char servoNum, unsigned int value);

#endif


// Servo PWM Command Timing Diagram by Using PCA9685:
//       _____                                 _____                                 _____
// _____|     |_______________________________|     |_______________________________|     |______
//      |<-1->|
//      |<-----------------2----------------->|
// 1: ServoPosition		0 ~  205  ~ 410
//    PCA9685 Count   102 ~  307  ~ 512
//    Period Range  0.5ms ~ 1.5ms ~ 2.5ms
// 2: ServoPeriodCount	0     ~     4096
// ServoBasePeriod: 4096 = PWM one Wave(2) Frequency: 50Hz(20ms)