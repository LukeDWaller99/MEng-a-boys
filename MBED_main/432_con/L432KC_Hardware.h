#ifndef __L432KC_HARDWARE_H__
#define __L432KC_HARDWARE_H__
//NUCLEO-L432KC HARDWARE

#define L4_USER_LED_GREEN PB_3

// //SPARE
#define SP_D7 D7
#define SP_D8 D8
#define SP_A4 A4
#define SP_A5 A5

//LCD
#define LCD_RS D1 //PA_9
#define LCD_E A6 //PA_7
#define LCD_RW A7 //PA_2
#define LCD_D4 D4 //PB_7
#define LCD_D5 D5 //PB_6
#define LCD_D6 D6 //PB_1
#define LCD_D7 D9 //PA_8

//SPI
#define mosi D2 //PA_12 
#define miso D10 //PA_11
#define SCK  A1 //PA_1
#define CS D3 //PB_0 // mosi, miso, sclk, nSS

//D-PAD BUTTONS
#define D_UP A0 //PA_0
#define D_LEFT A2 //PA_3
#define D_RIGHT D11 //PB_5
#define D_DOWN A3 //PA_4
#define D_SEL D12 //PB_4 same as MISO
#define D_BACK D13 //PB_3 same as SCK

// //SPI Pins - AS IN MANUAL
// #define MOSI PA_12 //D2
// #define MISO PA_11 //D10
// #define SCK PA_1 //A1
// //#define SSEL A3//PA_4/A3 worked but taken

#endif