#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// pins for nRF24L01
#define MOSI    PA_12   // D2 
#define MISO    PA_11   // D10
#define SCK     PA_1    // A1
#define CSN     PB_4    // D12
#define CE      PB_5    // D11
#define IRQ     PA_8    // D9

// joystick pins
#define L_PITCH PA_0    // A0
#define L_ROLL  PA_7    // A6
#define R_PITCH PA_6    // A5
#define R_ROLL  PA_5    // A4

// input buttons
#define BTN1    PB_3    // D13
#define BTN2    PB_1   // D3
#define BTN3    PB_7    // D4
#define BTN4    PB_6    // D5

// //input switches
#define SW1     PC_15   // D8
#define SW2     PC_14   // D7

// leds
#define LED_1   PA_10   // D0
#define LED_2   PA_9    // D1

// // buzzer
#define BUZZER  PB_0   // D6

// // potentiometers 
#define POT1    PA_3    // A2
#define POT2    PA_4    // A3

#endif