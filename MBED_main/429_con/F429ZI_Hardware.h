#ifndef __HARDWARE_H__
#define __HARDWARE_H__
//NUCLEO-F429ZI HARDWARE
#include <mbed.h>

//onboard peripherals
#define USR_BTN PC_13
#define USER_LED_GREEN PB_0
#define USER_LED_BLUE PB_7
#define USER_LED_RED PB_14

//Comms
#define CLK_1 PB_3
#define MISO_1 PB_4
#define MOSI_1 PB_5
#define CS_1 PD_14

// joystick pins
#define L_PITCH PC_3   
#define L_ROLL  PF_3
#define R_PITCH PC_0
#define R_ROLL  PA_3 

//SWITCHES
#define ASCEND PB_9 //3
#define DESCEND PB_8 //4
#define MOTOR_MODE_1 PF_2  //5
#define MOTOR_MODE_2 PH_1  //6
#define LIGHTS PG_2 //7
#define MOTOR_EN PF_10 //8
#define MOTOR_DE PF_5 //9
#define BRAKE_MODE PC_11 //10
#define REV_MODE PC_12 //11
#define SWITCH_1 PD_0 //1
#define SWITCH_2 PD_1 //2

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
#define BUZZER  PA_6
#define VIB_MOTOR PA_5

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

// void SW_BRAKE_IRQ();
// void SW_REV_IRQ();
// void SW_M_EN_IRQ();
// void SW_M_DE_IRQ(); 