/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

#include <cstdio>
#include <mbed.h>
#include <nRF24L01P.h>
#include <string>
#include "Buzzer.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "nfc_errors.h"

#define TESTING_MODE 0 // testing mode = 1 - NUCELO-F429ZI
#define TRANSFER_SIZE 10

#define MULTIPLYING_FACTOR  2.0f
#define POT_OFFSET          1.0f

#if TESTING_MODE == 1
    #include "TESTING_HARDWARE.h"

#elif TESTING_MODE == 0
    #include "HARDWARE.h"

#endif

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

InterruptIn Btn_1(BTN1), Btn_2(BTN2), Btn_3(BTN3), Btn_4(BTN4);  
DigitalIn SW_1(SW1), SW_2(SW2);        
DigitalOut led_1(LED_1), led_2(LED_2);                                              
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL), Pot_1(POT1), Pot_2(POT2);    
Buzzer buzzer(BUZZER);

char txData[TRANSFER_SIZE], 
     rxData[TRANSFER_SIZE];

char txLeftPitch[TRANSFER_SIZE], 
     txLeftRoll[TRANSFER_SIZE],
     txRightPitch[TRANSFER_SIZE], 
     txRightRoll[TRANSFER_SIZE], 
     txPot1[TRANSFER_SIZE], 
     txPot2[TRANSFER_SIZE];

int txDataCnt = TRANSFER_SIZE, rxDataCnt = 0;

Thread LEDThread, ButtonThread, PotThread, RadioThread;

Mutex PotLock;

float potVals[6], oldPotVals[6];


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

    led_1 = 1;
    buzzer = 1;
    wait_us(1000000);
    buzzer = 0;

    PotThread.start(PotMethod);
    RadioThread.start(RadioMethod);
    LEDThread.start(toggleLEDs);
    ButtonThread.start(ButtonThreadMethod);
    Btn_1.rise(Btn_1IRQ);
    Btn_2.rise(Btn_2IRQ);
    Btn_3.rise(Btn_3IRQ);
    Btn_4.rise(Btn_4IRQ);

    while (true) {
        // nRF24L01.write(0, txData, txDataCnt);
        // wait_us(1000000);
        // if (nRF24L01.readable(0)) {
        //     rxDataCnt = nRF24L01.read(0, rxData, sizeof(rxData));
        //     printf("%s\n", rxData);
        // }
    }
}

void PotMethod(){

    while(true){

        PotLock.trylock_for(10ms);
            potVals[0] = (L_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[1] = (L_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[2] = (R_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[3] = (R_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[4] = (Pot_1.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[5] = (Pot_2.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
        PotLock.unlock();

        // printf("Left Pitch: %f\n", potVals[0]);
        // printf("Left Roll: %f\n", potVals[1]);
        // printf("Right Pitch: %f\n", potVals[2]);
        // printf("Right Roll: %f\n", potVals[3]);
        // printf("Pot 1: %f\n", potVals[4]);
        // printf("Pot 2: %f\n", potVals[5]);

        // ThisThread::sleep_for(2s);
        
    }
}

void RadioMethod(){
    printf("Radio Thread Started\n");
    while(true){
        PotLock.trylock_for(10ms);
        sprintf(txLeftPitch, "%.1f", potVals[0]);
        sprintf(txLeftRoll, "%.1f", potVals[1]);
        sprintf(txRightPitch, "%.1f", potVals[2]);
        sprintf(txRightRoll, "%.1f", potVals[3]);
        sprintf(txPot1, "%.1f", potVals[4]);
        sprintf(txPot2, "%.1f", potVals[5]);
        PotLock.unlock();

        for (int i = 0; i > 6; i++){
            if (potVals[i] == oldPotVals[i]){
                 nRF24L01.write(0, txData, txDataCnt);
            }
        }
        // buzzer = 1;
        // ThisThread::sleep_for(500ms);
        // buzzer = 0;

        // ThisThread::sleep_for(5s);

        for (int i = 0; i > 6; i++){
            oldPotVals[i] = potVals[i];
        }
    }
}

void toggleLEDs(){
    printf("LED Thread Started \n");
    while (true) {
    led_1 = !led_1;
    led_2 = !led_2;
    ThisThread::sleep_for(1s);
    }
}

void ButtonThreadMethod(){
    printf("Button Thread Started\n");
    while (true) {
        buzzer = 0;
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        printf("Flag = %d\n", flag);
        if (flag == 1) {
            printf("Button 1 pressed\n");
        }
        else if (flag == 2) {
            printf("Button 2 pressed\n");
        }
        else if (flag == 4) {
            printf("Button 3 pressed\n");
        }
        else if (flag == 8) {
            printf("Button 4 pressed\n");
        }
        else {
            printf("ERROR\n");
        }
        flag = 0;
        // ThisThread::sleep_for(500ms);
    }
}

void Btn_1IRQ(){
    ButtonThread.flags_set(1);
}

void Btn_2IRQ(){
    ButtonThread.flags_set(2);
}

void Btn_3IRQ(){
    ButtonThread.flags_set(4);
}

void Btn_4IRQ(){
    ButtonThread.flags_set(8);
}
