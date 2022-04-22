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
#define BTN_1   PG_9
#define BTN_2   PE_7
#define SW_1    PE_8
#define SW_2    PE_10
#define SW_3    PE_12
#define SW_4    PF_14
#define SW_5    PE_13
#define SW_6    PE_14

// IR Sensors
#define IR_1    PB_1
#define IR_2    PC_2
#define IR_3    PF_4
#define IR_4    PB_6

// Buzzer
#define BUZZER  PB_8

#endif