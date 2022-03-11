/**
 * @file HARDWARE.h
 * 
 * @author Luke Waller
 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// pins for nRF24L01
#define MOSI    PB_5
#define MISO    PB_4
#define SCK     PB_3
#define CSN     PA_4
#define CE      PB_13
#define IRQ     PB_12

// BLDC motor pins
#define FWD_LHS_MOTOR   PE_5
#define FWD_RHS_MOTOR   PE_6
#define REV_LHS_MOTOR   PF_8
#define REV_RHS_MOTOR   PF_9

//Conveyer Motors
#define CONV_MOTOR_1_A      PD_4
#define CONV_MOTOR_1_B      PD_5
#define CONV_MOTOR_2_A      PD_6
#define CONV_MOTOR_2_B      PD_7
#define CONV_MOTOR_1_ENABLE PD_3
#define CONV_MOTOR_2_ENABLE PE_2

#endif