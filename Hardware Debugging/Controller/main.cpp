/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <mbed.h>
#include <nRF24L01P.h>
#include <string>
#include "Buzzer.h"
#include "Callback.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "EventQueue.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "HARDWARE.h"
#include "TRANSMISSION_CODES.h"

#define TRANSFER_SIZE   5
#define DEFAULT_PIPE    0 // set the defauly pipe for the nRF24L01

#define MULTIPLYING_FACTOR  2.0f
#define POT_OFFSET          1.0f

#define RADIO_QUEUE_LENGTH 32


// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
// nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

DigitalIn BT1(BTN1), BT2(BTN2), BT3(BTN3), SW_1(SW1);        
DigitalOut LED(LED_1);                                             
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL);   
Buzzer buzzer(BUZZER);


// create an array of outputs for the leds for the output
int main() {

    printf("Starting Board...\n");

    LED = 1;
    buzzer.chime();

    float val;

    while (true) {

        val = L_Pitch.read();

        if (BTN1 == 1){buzzer=1;}
        else {buzzer=0;}

        printf("%f\n", val);
    }
}
