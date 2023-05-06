#include <cstdio>
#include <cstdlib>
#include <mbed.h>
#include <string>
#include "Buzzer.h"
#include "DigitalOut.h"
#include "EventQueue.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "F429ZI_Hardware.h"

//Onboard Peripherals 
DigitalIn USER_BTN(USR_BTN);
DigitalOut USER_GREEN(USER_LED_GREEN);
DigitalOut USER_RED(USER_LED_RED);
DigitalOut USER_BLUE(USER_LED_BLUE);

DigitalIn Switch_1(SWITCH_1);
DigitalIn Switch_2(SWITCH_2);
//DigitalIn USER_BTN(USR_BTN);
DigitalIn SW_ASCED(ASCEND);
DigitalIn SW_DESCEND(DESCEND);
DigitalIn SW_LIGHTS(LIGHTS);
DigitalIn SW_BRAKE(BRAKE_MODE);
DigitalIn SW_REV(REV_MODE);
DigitalIn SW_M_MODE_1(MOTOR_MODE_1);
DigitalIn SW_M_MODE_2(MOTOR_MODE_2);
DigitalIn SW_M_EN(MOTOR_EN);
DigitalIn SW_M_DE(MOTOR_DE);

DigitalOut Switch_1_led(SWITCH_1_LED);
DigitalOut Switch_2_led(SWITCH_2_LED);
// DigitalOut USER_GREEN(USER_LED_GREEN);
// DigitalOut USER_RED(USER_LED_RED);
// DigitalOut USER_BLUE(USER_LED_BLUE);
DigitalOut M_MODE_1_LED(MOTOR_MODE_1_LED);
DigitalOut M_MODE_2_LED(MOTOR_MODE_2_LED);
DigitalOut Lights_LED(LIGHTS_LED);
DigitalOut M_EN_LED(EN_LED);
DigitalOut M_DE_LED(DE_LED);

#define TEST_BLINK_RATE 500ms
int USR_BTN_COUNT = 0;

int main()
{
    
	printf("Starting Board...\n");

    if(Switch_1 == 1){
        Switch_1_led = 1;
        printf("SW1 HIGH");
    } else
    {
        Switch_1_led = 0;
    }

     if(Switch_2 == 1){
        Switch_2_led = 1;
        printf("SW2 HIGH");
    } else
    {
        Switch_2_led = 0;
    }

    while (true) {

        USER_GREEN = !USER_GREEN;
        ThisThread::sleep_for(TEST_BLINK_RATE);
        USER_BLUE = !USER_BLUE;
        ThisThread::sleep_for(TEST_BLINK_RATE);
        USER_RED = !USER_RED;
        ThisThread::sleep_for(TEST_BLINK_RATE);
    
    }
}
