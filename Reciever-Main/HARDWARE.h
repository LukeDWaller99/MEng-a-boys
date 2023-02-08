/**
 * @file HARDWARE.h
 * 
 * @author Luke Waller
 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// nRF24L01
#define MOSI    PB_5
#define MISO    PB_4
#define SCK     PB_3
#define CSN     PA_4
#define CE      PB_13
#define IRQ     PB_12

// BLDC motor pins
#define FWD_LHS_MOTOR   PE_6
#define FWD_RHS_MOTOR   PF_7
#define REV_LHS_MOTOR   PF_8
#define REV_RHS_MOTOR   PF_9

// Conveyer Motors
#define CONV_MOTOR_1_A      PD_4
#define CONV_MOTOR_1_B      PD_3
#define CONV_MOTOR_2_A      PE_2
#define CONV_MOTOR_2_B      PE_4
#define CONV_MOTOR_1_ENABLE PC_8
#define CONV_MOTOR_2_ENABLE PE_5

// LEDs
#define LED_1   PD_5
#define LED_2   PC_9
#define LED_3   PC_10
#define LED_4   PC_11
#define LED_5   PC_12
#define LED_6   PD_2
#define LED_7   PG_2
#define LED_8   PG_3
#define LED_9   PD_7
#define LED_10  PD_6

// Inputs
#define BTN_1   PG_9    // SW1 - working
#define BTN_2   PE_7    // SW2 - working
#define SW_1    PE_8    // SW3 - working
#define SW_2    PE_10   // SW4 - working
#define SW_3    PE_12   // SW5 - not in use
#define SW_4    PE_14   // SW6 - not in use 
#define SW_5    PF_14   // SW7 - not in use
#define SW_6    PE_13   // SW8 - not in use

// IR Sensors
#define IR_1    PB_1 // working
#define IR_2    PC_2 // not in use
#define IR_3    PF_4 // not in use
#define IR_4    PB_6 // working

// Buzzer
#define BUZZER  PB_8

// Low Battery Inputs
#define Bat_30_PERCENT PC_0
#define Bat_15_PERCENT PA_3

#endif