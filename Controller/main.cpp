/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

#include <cstdio>
#include <mbed.h>
#include <nRF24L01P.h>
#include <string>
#include "Buzzer.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "nfc_errors.h"

#define TESTING_MODE 0 // testing mode = 1 - NUCELO-F429ZI
#define TRANSFER_SIZE 10

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

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

InterruptIn Btn_1(BTN1), Btn_2(BTN2), Btn_3(BTN3), Btn_4(BTN4);           
DigitalOut led_1(LED_1), led_2(LED_2);                                               
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL), Pot_1(POT1), Pot_2(POT2);    
Buzzer buzzer(BUZZER);


DigitalOut LED(LED1);

char txData[TRANSFER_SIZE], rxData[TRANSFER_SIZE];
int txDataCnt = TRANSFER_SIZE, rxDataCnt = 0;

// Thread BtnThread, SerialThread, PotThread;
Thread LEDThread, ButtonThread, PotThread, RadioThread;

Mutex PotLock;

float potVals[6];

// int quantisePotVal (int EightBitPotVal){
//     int LedMask = 0;
//     switch (EightBitPotVal) {
//     case 1:
//     return LedMask = 1;
//     case 2:
//     return LedMask = 3;
//     case 3:
//     return LedMask = 7;
//     case 4:
//     return LedMask = 15;
//     case 5:
//     return LedMask = 31;
//     case 6:
//     return LedMask = 63;
//     case 7:
//     return LedMask = 127;
//     default:
//     return LedMask;
//     }
// }

// void BtnMethod(){
//     while(true){

//     }   
// }

// void SerialMethod(){
//     while(true){

//     }
// }

void PotMethod();

void toggleLEDs();
void ButtonThreadMethod();
void RadioMethod();
void Btn_1IRQ();
void Btn_2IRQ();
void Btn_3IRQ();
void Btn_4IRQ();



// create an array of outputs for the leds for the output
int main() {

    nRF24L01.powerUp();
 

// Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output power : %d dBm\n",  nRF24L01.getRfOutputPower() );
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate() );
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress() );
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress() );

    nRF24L01.setTransferSize(TRANSFER_SIZE);
 
    // nRF24L01.setReceiveMode();
    nRF24L01.setTransmitMode();
    nRF24L01.enable();

    // led_1 = 1;

    PotThread.start(PotMethod);
    RadioThread.start(RadioMethod);
    // LEDThread.start(toggleLEDs);
    // ButtonThread.start(ButtonThreadMethod);
    // Btn_1.rise(Btn_1IRQ);
    // Btn_2.rise(Btn_2IRQ);
    // Btn_3.rise(Btn_3IRQ);
    // Btn_4.rise(Btn_4IRQ);
    
    // // buzzer.chime(10000000, "E","F","G", Buzzer::HIGHER);
    // buzzer.chime(10000000);

    // buzzer = "G";   // operator overload to set note 
    // // buzzer = 1;     // operator overload to turn buzzer on and off
    // buzzer = 1.0f;  // operator overload to set period of buzzer on
    // // buzzer = 0;

    // // led_1 = 1;
    // // led_2 = 1;

    // buzzer = 1;
    // wait_us(100000);
    // buzzer = 0;

    while (true) {
        LED = !LED;
        // led_1 = 1;
        // led_2 = 1;
        // if (Btn_1 == 1) {
        // led_1 = 1;
        // }
        // else {
        // led_1 = 0;
        // }
        // else {
        // led_1 = 0;
        // }
    // LEDs = ledMask | allOn;
    // potVal = L_Pitch.read_u16();
    // eightBitPotVal = potVal >> 13;
    // quantisedVal = quantisePotVal(eightBitPotVal);
    // ledMask = quantisedVal << 2;
    // // printf("%d\n", quantisedVal);
    // wait_us(10);
        // nRF24L01.write(0, txData, txDataCnt);
        // wait_us(1000000);
        // if (nRF24L01.readable(0)) {
        //     rxDataCnt = nRF24L01.read(0, rxData, sizeof(rxData));
        //     for(int i = 0; rxDataCnt > 0; rxDataCnt--, i++){
        //         printf("%c\n",rxData[i]);
        //     }
        // }
    }
}

void PotMethod(){

    while(true){

        PotLock.trylock_for(10ms);
            potVals[0] = L_Pitch.read();
            potVals[1] = R_Pitch.read();
            potVals[2] = L_Roll.read();
            potVals[3] = R_Roll.read();
            potVals[4] = Pot_1.read();
            potVals[5] = Pot_2.read();
        PotLock.unlock();

        // printf("Left Pitch: %f\n", potVals[0]);
        // printf("Left Roll: %f\n", potVals[1]);
        // printf("Right Pitch: %f\n", potVals[2]);
        // printf("Right Roll: %f\n", potVals[3]);
        // printf("Pot 1: %f\n", potVals[4]);
        // printf("Pot 2: %f\n", potVals[5]);

        ThisThread::sleep_for(2s);
        
    }
}

void RadioMethod(){
    while(true){
        PotLock.trylock_for(10ms);
        for(int i = 0; i < 6; i++){
            printf("%f\n", potVals[i]);
            sprintf(txData, "%.2f", potVals[i]);
            printf("%s\n", txData);
        }
        PotLock.unlock();

        nRF24L01.write(0, txData, txDataCnt);

        ThisThread::sleep_for(5s);
    }
}

void toggleLEDs(){
    while (true) {
    led_1 = !led_1;
    led_2 = !led_2;
    ThisThread::sleep_for(1s);
    }
}

// void ButtonThreadMethod(){
//     printf("Thread Started\n");
//     while (true) {
//         buzzer = 0;
//         ThisThread::flags_wait_any(0x7fffffff, false);
//         buzzer = 1;
//         int flag = ThisThread::flags_get();
//         printf("Flag = %d\n", flag);
//         if (flag == 1) {
//             printf("Button 1 pressed\n");
//         }
//         else if (flag == 2) {
//             printf("Button 2 pressed\n");
//         }
//         else if (flag == 3) {
//             printf("Button 3 pressed\n");
//         }
//         else if (flag == 4) {
//             printf("Button 4 pressed\n");
//         }
//         else {
//             printf("ERROR\n");
//         }
//         flag = 0;
//                 ThisThread::sleep_for(500ms);
//         ThisThread::flags_clear(0x7fffffff);
//     }
// }

// void Btn_1IRQ(){
//     ButtonThread.flags_set(1);
// }

// void Btn_2IRQ(){
//     ButtonThread.flags_set(2);
// }

// void Btn_3IRQ(){
//     ButtonThread.flags_set(3);
// }

// void Btn_4IRQ(){
//     ButtonThread.flags_set(4);
// }
