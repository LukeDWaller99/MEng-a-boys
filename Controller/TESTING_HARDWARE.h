#ifndef __TESTING_HARDWARE_H__
#define __TESTING_HARDWARE_H__

// pins used on the MSB 

#include <PinNames.h>

// pins for nRF24L01
#define MOSI    PB_5
#define MISO    PB_4
#define SCK     PB_3
#define CS      PA_11
#define CE      PA_9
#define IRQ     PB_1

// joystick pins
#define L_PITCH PA_0
#define L_ROLL  PC_0
#define R_PITCH PC_3
#define R_ROLL  PF_3

// input buttons
#define BTN1    PA_7  
#define BTN2    PF_2
#define BTN3    PF_1
#define BTN4    PF_0

//input switches
#define SW1     PD_7
#define SW2     PD_6

// leds
#define LED_1   PD_0
#define LED_2   PD_1

// buzzer
#define BUZZER  PB_13

// potentiometers 
#define POT1    PF_5
#define POT2    PF_10

#endif