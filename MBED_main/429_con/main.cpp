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

DigitalIn Switch_1(SWITCH_1);
DigitalIn Switch_2(SWITCH_2);
DigitalIn USER_BTN(USR_BTN);

DigitalOut Switch_1_led(SWITCH_1_LED);
DigitalOut Switch_2_led(SWITCH_2_LED);
DigitalOut USER_GREEN(USER_LED_GREEN);
DigitalOut USER_RED(USER_LED_RED);
DigitalOut USER_BLUE(USER_LED_BLUE);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


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
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
