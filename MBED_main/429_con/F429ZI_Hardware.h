#ifndef __HARDWARE_H__
#define __HARDWARE_H__
//NUCLEO-F429ZI HARDWARE
#include <mbed.h>

//onboard peripherals
#define USR_BTN PC_13
#define USER_LED_GREEN PB_0
#define USER_LED_BLUE PB_7
#define USER_LED_RED PB_14

//SPI PINS DEFINED ON PCB
// #define CLK_1 PB_3
// #define MISO_1 PB_4
// #define MOSI_1 PB_5

//SPI PINS DEFINED IN EXAMPLES
//#define CS_1 PD_13
#define CLK_2 D13   //PA_5
#define MISO_2 PB_5 //PA_7 or PB_5 - D11
#define MOSI_2 D12 //PA_6


//Comms
#define CLK_1 PB_3
#define MISO_1 PB_4
#define MOSI_1 PB_5
#define CS_1 PD_13

// joystick pins
#define L_PITCH PC_3   
#define L_ROLL  PF_3
#define R_PITCH PC_0
#define R_ROLL  PA_3 

#define PITCH_UPPER_LIMIT  1 
#define PITCH_LOWER_LIMIT  -1
#define ROLL_UPPER_LIMIT   1
#define ROLL_LOWER_LIMIT   -1

#define TRANSFER_SIZE   5
#define MULTIPLYING_FACTOR  2.0f
#define POT_OFFSET          1.0f

#define LEFT_PITCH_FWD  '1','1','0','0','\0'
#define LEFT_ROLL_FWD   '1','2','0','0','\0'
#define RIGHT_PITCH_FWD '1','3','0','0','\0'
#define RIGHT_ROLL_FWD  '1','4','0','0','\0'

#define LEFT_PITCH_REV  '1','1','1','0','\0'
#define LEFT_ROLL_REV   '1','2','1','0','\0'
#define RIGHT_PITCH_REV '1','3','1','0','\0'
#define RIGHT_ROLL_REV  '1','4','1','0','\0'

//SWITCHES
#define ASCEND PB_8 //3
#define DESCEND PB_9 //4
#define MOTOR_MODE_1 PF_2  //5
#define MOTOR_MODE_2 PH_1  //6
#define LIGHTS PG_2 //7
#define MOTOR_EN PF_10 //8
#define MOTOR_DE PF_5 //9
#define BRAKE_MODE PD_2 //10
#define REV_MODE PC_12 //11
#define SWITCH_1 PD_0 //1
#define SWITCH_2 PD_1 //2
#define KILL_SWITCH PC_8

// // input buttons
// #define BTN1    PF_5 // D1
// #define BTN2    PF_10 // D6
// #define BTN3    PF_0 // A2

// General LEDs
#define LED_1 PD_14
#define LED_2 PD_15
#define SWITCH_1_LED PF_9
#define SWITCH_2_LED PG_1
#define MOTOR_MODE_1_LED PG_0
#define MOTOR_MODE_2_LED PH_0
#define LIGHTS_LED PG_3
#define EN_LED PD_6
#define DE_LED PD_7 
#define ASCEND_LED PB_15
#define DESCEND_LED PC_6
#define KILL_LED PC_9
#define REV_LED PC_10
#define BRAKE_LED PC_11

// Buzzer and Vibration Motor
// #define BUZZER  PA_6
// #define VIB_MOTOR PA_5

//Collision LEDs
#define COL_SENSE_1 PE_7
#define COL_SENSE_2 PD_12
#define COL_SENSE_3 PE_10
#define COL_SENSE_4 PD_11
#define COL_SENSE_5 PE_14
#define COL_SENSE_6 PE_15
#define COL_SENSE_7 PE_8
#define COL_SENSE_8 PE_11


#endif