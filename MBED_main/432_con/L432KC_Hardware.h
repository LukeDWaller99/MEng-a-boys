#ifndef __L432KC_HARDWARE_H__
#define __L432KC_HARDWARE_H__
//NUCLEO-L432KC HARDWARE

#define L4_USER_LED_GREEN PB_3

//LCD
#define LCD_RS D1
#define LCD_E A6
#define LCD_RW A7
#define LCD_D4 D4
#define LCD_D5 D5
#define LCD_D6 D6
#define LCD_D7 D7

//SPI Pins - AS IN MANUAL
#define MOSI PA_12 //D2
#define MISO PA_11 //D10
#define SCK PA_1 //A1
#define SSEL A3//PA_4/A3 worked but taken

#endif