/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

#include <cstdio>
#include <mbed.h>
#include <nRF24L01P.h>

// for initial test, map the pot value to the led strip on the MSB as a test
// need to create an analog in instance of the pot 
AnalogIn pot(PA_0);
int potVal;
int eightBitPotVal;
int quantisedVal;
PortOut LEDs(PortE);


int redOn = 4096; //    0b0001000000000000;
int greenOn = 8192; //  0b0010000000000000;
int blueOn = 16384; //  0b0100000000000000;
int ledMask = 1020; //  0b0000001111111100;
int allOn =  0b0111000000000000;

int quantisePotVal (int EightBitPotVal){
    int LedMask = 0;
    switch (EightBitPotVal) {
    case 1:
    return LedMask = 1;
    case 2:
    return LedMask = 3;
    case 3:
    return LedMask = 7;
    case 4:
    return LedMask = 15;
    case 5:
    return LedMask = 31;
    case 6:
    return LedMask = 63;
    case 7:
    return LedMask = 127;
    default:
    return LedMask;
    }
}

// create an array of outputs for the leds for the output
int main() {
    

    while (true) {
    LEDs = ledMask | allOn;
    potVal = pot.read_u16();
    eightBitPotVal = potVal >> 13;
    quantisedVal = quantisePotVal(eightBitPotVal);
    ledMask = quantisedVal << 2;
    // printf("%d\n", quantisedVal);
    wait_us(10);
    }
}
