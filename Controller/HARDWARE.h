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

// joystick pins
#define L_PITCH PA_3    // A0
#define L_ROLL  PC_0    // A1
#define R_PITCH PC_3    // A3
#define R_ROLL  PF_3   // A4

// input buttons
#define BTN1    PF_5 // D1
#define BTN2    PF_10 // D6
#define BTN3    PF_0 // A2

//input switches
#define SW1     PF_2  // D3 

// leds
#define LED_1   PF_1 // D0


// buzzer
#define BUZZER  PA_7 // D5


#endif