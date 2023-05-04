#include <cstdio>
#include <cstdlib>
#include <mbed.h>
#include <string>
#include "DigitalOut.h"
#include "EventQueue.h"
#include "ThisThread.h"
#include "hardware.h"


DigitalIn Switch_1(SWITCH_1);
DigitalIn Switch_2(SWITCH_2);


DigitalOut Switch_1_led(SWITCH_1_LED);
DigitalOut Switch_2_led(SWITCH_2_LED);

int main() {
	printf("Starting Board...\n");

    if(Switch_1 == 1){
        Switch_1_led = 1;
    } else
    {
        Switch_1_led = 0;
    }

     if(Switch_2 == 1){
        Switch_2_led = 1;
    } else
    {
        Switch_2_led = 0;
    }
}