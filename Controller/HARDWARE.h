#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// // pins for nRF24L01
// #define MOSI    PA_12   // D2
// #define MISO    PA_11   // D10
// #define SCK     PB_3    // D13
// #define CSN     PB_4    // D12
// #define CE      PB_5    // D11
// #define IRQ     PA_8    // D9 

// // joystick pins
// #define L_PITCH PA_0    // A0
// #define L_ROLL  PA_1    // A1
// #define R_PITCH PA_4    // A3
// #define R_ROLL  PA_5    // A4

// // input buttons
// #define BTN1    PA_9 // D1
// #define BTN2    PB_1 // D6
// #define BTN3    PA_3 // A2

// // //input switches
// #define SW1     PB_0  // D3 

// // leds
// #define LED_1   PA_10 // D0


// // buzzer
// #define BUZZER  PB_6 // D5

// nRF24L01
#define MOSI    PB_5
#define MISO    PB_4
#define SCK     PB_3
#define CSN     PA_4
#define CE      PB_13
#define IRQ     PB_12

// joystick pins
#define L_PITCH PA_3    // A0
#define L_ROLL  PC_0    // A1
#define R_PITCH PC_3    // A3
#define R_ROLL  PF_3    // A4

// input buttons
#define BTN1    PF_5 // D1
#define BTN2    PF_10 // D6
#define BTN3    PF_0 // A2

// //input switches
#define SW1     PF_2  // D3 

// leds
#define LED_1   PF_1 // D0


// buzzer
#define BUZZER  PA_7 // D5


#endif