#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// pins for nRF24L01
#define MOSI    PA_12   // D2  - good 
#define MISO    PA_11   // D10 - good 
#define SCK     PB_3    // D13 - good 
#define CSN     PB_4    // D12 - good 
#define CE      PB_5    // D11 - good
#define IRQ     PA_8    // D9  - good 

// joystick pins
#define L_PITCH PA_0    // A0
#define L_ROLL  PA_1    // A1
#define R_PITCH PA_4    // A3
#define R_ROLL  PA_5    // A4

// input buttons
#define BTN1    PA_9 // good
#define BTN2    PB_1 // D6 - good
#define BTN3    PA_3 // good

// //input switches
#define SW1     PB_0  // D3 - good  

// leds
#define LED_1   PA_10 // D0 - good 


// buzzer
#define BUZZER  PB_6 // D5 - good

#endif