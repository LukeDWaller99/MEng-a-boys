#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <PinNames.h>

// pins for nRF24L01
#define MOSI    PB_5
#define MISO    PB_4
#define SCK     PB_3
#define CS      PA_11
#define CE      PA_9
#define IRQ     PB_1

// joystick pins
#define L_PITCH PA_2
#define L_ROLL  PA_7
#define R_PITCH PA_6
#define R_ROLL  PA_5

// input buttons
#define BTN1    PA_12 
#define BTN2    PB_0
// #define BTN3    PB_7
// #define BTN4    PB_6

//input switches
#define SW1     PB_6
#define SW2     PB_7

// leds
#define LED_1   PA_10
#define LED_2   PA_9

// buzzer
#define BUZZER  PA_1

// potentiometers 
#define POT1    PA_3
#define POT2    PA_4

#endif