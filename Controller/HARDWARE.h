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
#define L_PITCH PA_0
#define L_ROLL  PA_7
#define R_PITCH PA_6
#define R_ROLL  PA_5

// input buttons
#define BTN1    PB_3 
#define BTN2    PB_0
#define BTN3    PB_7
#define BTN4    PB_6

// //input switches
#define SW1     PC_14
#define SW2     PC_15

// leds
#define LED_1   PA_10
#define LED_2   PA_9

// // buzzer
#define BUZZER  PA_9

// // potentiometers 
#define POT1    PA_3
#define POT2    PA_4

#endif