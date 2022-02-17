/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

#include <cstdio>
#include <mbed.h>
#include <nRF24L01P.h>
#include "Buzzer.h"

#define TESTING_MODE 1

#if TESTING_MODE == 1
    #include "TESTING_HARDWARE.h"

#elif TESTING_MODE == 0
    #include "HARDWARE.h"

#endif


// for initial test, map the pot value to the led strip on the MSB as a test
// need to create an analog in instance of the pot 

// Test Code setup for dummy operation on the UoP MSB - will be deleted for final controller code
// PortOut LEDs(PortE);
// int potVal;
// int eightBitPotVal;
// int quantisedVal;
// int redOn = 4096; //    0b0001000000000000;
// int greenOn = 8192; //  0b0010000000000000;
// int blueOn = 16384; //  0b0100000000000000;
// int ledMask = 1020; //  0b0000001111111100;
// int allOn =  0b0111000000000000;

DigitalIn Btn_1(BTN1), Btn_2(BTN2), SW_1(SW1), SW_2(SW2);          
DigitalOut led_1(LED_1), led_2(LED_2);                                                
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL), Pot_1(POT1), Pot_2(POT2);    
Buzzer buzzer(BUZZER);

// MOSI, MISO, SCK, CS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CS, CE, IRQ);

Thread BtnThread, SerialThread, PotThread;

Mutex PotLock;

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

void BtnMethod(){
    while(true){

    }   
}

void SerialMethod(){
    while(true){

    }
}

void PotMethod();


// create an array of outputs for the leds for the output
int main() {

    // BtnThread.start(BtnMethod);
    PotThread.start(PotMethod);
    
    // // buzzer.chime(10000000, "E","F","G", Buzzer::HIGHER);
    // // buzzer.chime(10000000)

    // buzzer = "C";   // operator overload to set note 
    // buzzer = 1;     // operator overload to turn buzzer on and off
    // buzzer = 0.5f;  // operator overload to set period of buzzer on
    // buzzer = 0;

    led_1 = 1;
    led_2 = 1;

    buzzer = 1;
    wait_us(100000);
    buzzer = 0;

    while (true) {
    // LEDs = ledMask | allOn;
    // potVal = L_Pitch.read_u16();
    // eightBitPotVal = potVal >> 13;
    // quantisedVal = quantisePotVal(eightBitPotVal);
    // ledMask = quantisedVal << 2;
    // // printf("%d\n", quantisedVal);
    // wait_us(10);
    }
}

void PotMethod(){

    double L_PitchVal;
    double L_RollVal;
    double R_PitchVal;
    double R_RollVal;
    double Pot_1Val;
    double Pot_2Val;

    while(true){

        PotLock.lock();
            L_PitchVal = L_Pitch.read();
            R_PitchVal = R_Pitch.read();
            L_RollVal = L_Roll.read();
            R_RollVal = R_Roll.read();
            Pot_1Val = Pot_1.read();
            Pot_2Val = Pot_2.read();
        PotLock.unlock();

        printf("%f\n", Pot_1Val);
        wait_us(1000000);
        
    }
}
