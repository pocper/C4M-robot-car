// Global

#define SERVO_HEADER 0xB0
#define SERVO_ENDING 0xB0
#define SERVO_EN_HEADER 0xB1
#define SERVO_EN_ENDING 0xB1
#define MOVEMENT_HEADER 0xB2
#define MOVEMENT_ENDING 0xB2
#define SENSOR_HEADER 0xB3
#define SENSOR_ENDING 0xB3

#define ERR_HEADER 0xFF

#define RegAdd_Multi_Val 1
#define RegAdd_L_Lim 2
#define RegAdd_U_Lim 3
#define RegAdd_Enable_Channel 4
#define RegAdd_Enable_Power 5
#define RegAdd_Enable_Protect 6

#define RegAdd_Single_Val 10

#define Servo_num 11
#define SERVO_LIMIT_MIN 72
#define SERVO_LIMIT_MAX 338

// Master

#define SERVO_POS_HEADER 0
#define SERVO_POS_REGADD 1
#define SERVO_POS_DATA 2
#define SERVO_POS_ENDING 3

#define SERVO_EN_POS_HEADER 0
#define SERVO_EN_POS_REGADD 1
#define SERVO_EN_POS_DATA 2
#define SERVO_EN_POS_ENDING 3

#define SERVO_EN_REGADD_DISABLE_ARM 0xFE
#define SERVO_EN_REGADD_DISABLE_WHEEL 0xFF

#define MOVEMENT_POS_HEADER 0
#define MOVEMENT_POS_DATA 1
#define MOVEMENT_POS_ENDING 2

//Slave

#define M2S_HEADER 0xAA
#define M2S_ENDING 0xAA

#define SLAVE_POS_HEADER 0
#define SLAVE_POS_REGADD 1
#define SLAVE_POS_BYTES 2
#define SLAVE_POS_SINGLEBYTES 3
#define SLAVE_POS_DATA 4
#define SLAVE_POS_ENDING 5