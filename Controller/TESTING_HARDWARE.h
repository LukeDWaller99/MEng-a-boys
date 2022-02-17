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
#define L_PITCH PA_2
#define L_ROLL  PA_7
#define R_PITCH PA_6
#define R_ROLL  PA_5

// input buttons
#define BTN1    PG_0
#define BTN2    PG_1
#define BTN3    PG_2
#define BTN4    PG_3

//input switches
#define SW1     PB_6
#define SW2     PB_7

// leds
#define LED_1   PC_2
#define LED_2   PC_3

// buzzer
#define BUZZER  PB_13

// potentiometers 
#define POT1    PA_0
#define POT2    PA_0

#endif