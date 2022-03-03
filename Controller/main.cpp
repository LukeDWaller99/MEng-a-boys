/**
    @file Main.cpp
    Main file for Final Year Project - Luke Waller
**/

/*
    Transmittion Codes - 
    1xxx - POTs
        x1xx - Left Pitch
        x2xx - Left Roll
        x3xx - Right Pitch
        x4xx - Right Roll
            xx0x - Forwards
            xx1x - Reverse
                xxx0 - value of throttle
    2xxx - Buttons
        x1xx - Button 1
        x2xx - Button 2
        x3xx - Button 3
    3xxx - SW1 
        xx10 - ON
        xx01 - OFF
*/

#include <cmath>
#include <cstdio>
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

#define TRANSFER_SIZE   10
#define DEFAULT_PIPE    0 // set the defauly pipe for the nRF24L01

#define MULTIPLYING_FACTOR  2.0f
#define POT_OFFSET          1.0f

#define RADIO_QUEUE_LENGTH 32


// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

InterruptIn Btn_1(BTN1), Btn_2(BTN2), Btn_3(BTN3), SW_1(SW1);        
DigitalOut led_1(LED_1);                                             
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL);   
Buzzer buzzer(BUZZER);

// char txData[TRANSFER_SIZE], 
//      rxData[TRANSFER_SIZE];

// char txLeftPitch[TRANSFER_SIZE], 
//      txLeftRoll[TRANSFER_SIZE],
//      txRightPitch[TRANSFER_SIZE], 
//      txRightRoll[TRANSFER_SIZE], 

// char txLeftPitchTemp[TRANSFER_SIZE], 
//      txLeftRollTemp[TRANSFER_SIZE],
//      txRightPitchTemp[TRANSFER_SIZE], 
//      txRightRollTemp[TRANSFER_SIZE], 

// char txBTN1[TRANSFER_SIZE],
//      txBTN2[TRANSFER_SIZE],
//      txBTN3[TRANSFER_SIZE];

// char txSW1[TRANSFER_SIZE];

char rxData[TRANSFER_SIZE];
char txData[TRANSFER_SIZE];

struct stickData { 
    char LeftPitch[TRANSFER_SIZE], 
    LeftRoll[TRANSFER_SIZE], 
    RightPitch[TRANSFER_SIZE], 
    RightRoll[TRANSFER_SIZE], 
    LeftPitchTemp[TRANSFER_SIZE], 
    LeftRollTemp[TRANSFER_SIZE], 
    RightPitchTemp[TRANSFER_SIZE], 
    RightRollTemp[TRANSFER_SIZE];
};

struct btnData {
    char BTN1[TRANSFER_SIZE], 
    BTN2[TRANSFER_SIZE], 
    BTN3[TRANSFER_SIZE]; 
};

char txSW1[TRANSFER_SIZE];


int txDataCnt = TRANSFER_SIZE, rxDataCnt = 0;

Thread LEDThread, ButtonThread, PotThread, RadioThread;

Mutex PotLock;

float potVals[6], oldPotVals[6];


void PotMethod();

void toggleLEDs();
void ButtonThreadMethod();
void Btn_1IRQ();
void Btn_2IRQ();
void Btn_3IRQ();
void Btn_4IRQ();
void SW_1RisingIRQ();
void SW_1FallingIRQ();
void SW_2RisingIRQ();
void SW_2FallingIRQ();
void setBtnChar();
void setSWChar();



// create an array of outputs for the leds for the output
int main() {

    nRF24L01.powerUp();

// Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output power : %d dBm\n",  nRF24L01.getRfOutputPower());
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate());
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress());
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress());

    nRF24L01.setTransferSize(TRANSFER_SIZE);
 
    nRF24L01.setTransmitMode();

    nRF24L01.enable();

    txData[0] = 'T';
    txData[1] = 'E';
    txData[2] = 'S';
    txData[3] = 'T';

    nRF24L01.write(txData);

    setBtnChar();
    setSWChar();

    led_1 = 1;
    buzzer = 1;
    wait_us(1000000);
    buzzer = 0;

    PotThread.start(PotMethod);
    LEDThread.start(toggleLEDs);
    ButtonThread.start(ButtonThreadMethod);
    Btn_1.rise(Btn_1IRQ);
    Btn_2.rise(Btn_2IRQ);
    Btn_3.rise(Btn_3IRQ);
    SW_1.rise(SW_1RisingIRQ);
    SW_1.fall(SW_1FallingIRQ);

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

stickData tx[TRANSFER_SIZE];

int oldLeftPitchVal = 0;
int newLeftPitchVal = 0;

int oldLeftRollVal = 0;
int newLeftRollVal = 0;

int oldRightPitchVal = 0;
int newRightPitchVal = 0;

int oldRightRollVal = 0;
int newRightRollVal = 0;

    tx->LeftPitch[0] = 'L';
    tx->LeftPitch[1] = 'P';
    tx->LeftPitch[2] = ':';

    tx->LeftRoll[0] = 'L';
    tx->LeftRoll[1] = 'R';
    tx->LeftRoll[2] = ':';

    tx->RightPitch[0] = 'R';
    tx->RightPitch[1] = 'P';
    tx->RightPitch[2] = ':';

    tx->RightRoll[0] = 'R';
    tx->RightRoll[1] = 'R';
    tx->RightRoll[2] = ':';


    while(true){

        PotLock.trylock_for(10ms);
            potVals[0] = ((L_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET) * 10;
            potVals[1] = (L_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[2] = (R_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET;
            potVals[3] = (R_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET;

    newLeftPitchVal     = round(potVals[0]);
    newLeftRollVal      = round(potVals[1]);
    newRightPitchVal    = round(potVals[2]);
    newRightRollVal     = round(potVals[3]);

    if (oldLeftPitchVal != newLeftPitchVal){
        sprintf(tx->LeftPitchTemp, "%d", newLeftPitchVal);
        for (int i = 0; i < 3; i++) {tx->LeftPitch[i+3] = tx->LeftPitchTemp[i]; }
        nRF24L01.write(tx->LeftPitch);
    }
    if (oldLeftRollVal != newLeftRollVal){
        sprintf(tx->LeftRollTemp, "%d", newLeftRollVal);
        for (int i = 0; i < 3; i++) { tx->LeftRoll[i+3] = tx->LeftRollTemp[i]; }
        nRF24L01.write(tx->LeftRoll);
    }
    if (oldRightPitchVal != newRightPitchVal){
        sprintf(tx->RightPitchTemp, "%d", newRightPitchVal);
        for (int i = 0; i < 3; i++) { tx->RightPitch[i+3] = tx->RightPitchTemp[i]; }
        nRF24L01.write(tx->RightPitch);
    }
    if (oldRightRollVal != newRightRollVal){
        sprintf(tx->RightRollTemp, "%d", newRightRollVal);
        for (int i = 0; i < 3; i++) { tx->RightRoll[i+3] = tx->RightRollTemp[i]; }
        nRF24L01.write(tx->RightRoll);
    }

    oldLeftPitchVal = newLeftPitchVal;
    oldLeftRollVal = newLeftRollVal;
    oldRightPitchVal = newRightPitchVal;
    oldRightRollVal = newRightRollVal;

    PotLock.unlock();
    ThisThread::sleep_for(10ms);
    }
}

void ButtonThreadMethod(){
    btnData tx[TRANSFER_SIZE];

    tx->BTN1[0] = 'B';
    tx->BTN1[1] = 'T';
    tx->BTN1[2] = '1';

    tx->BTN2[0] = 'B';
    tx->BTN2[1] = 'T';
    tx->BTN2[2] = '2';

    tx->BTN3[0] = 'B';
    tx->BTN3[1] = 'T';
    tx->BTN3[2] = '3';

    printf("Button Thread Started\n");
    while (true) {
        buzzer = 0;
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        printf("Flag = %d\n", flag);
        if (flag == 1) {
            printf("Button 1 pressed\n");
            nRF24L01.write(tx->BTN1);
        }
        else if (flag == 2) {
            printf("Button 2 pressed\n");
            nRF24L01.write(tx->BTN2);
        }
        else if (flag == 4) {
            printf("Button 3 pressed\n");
            nRF24L01.write(tx->BTN3);
        }
        else if (flag == 8) {
            printf("Switch 1 ON\n");
            txSW1[4] = '1';
            nRF24L01.write(txSW1);
        }
        else if (flag == 16){
            printf("Switch 1 OFF\n");
            txSW1[4] = '0';
            nRF24L01.write(txSW1);
        }
        else {
            printf("ERROR\n");
        }
        flag = 0;
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

void SW_1RisingIRQ(){
    ButtonThread.flags_set(8);
}

void SW_1FallingIRQ(){
    ButtonThread.flags_set(16);
}

void setSWChar(){
    txSW1[0] = 'S';
    txSW1[1] = 'W';
    txSW1[2] = '1';
    txSW1[3] = ':';

}


void toggleLEDs(){
    printf("LED Thread Started \n");
    while (true) {
    led_1 = !led_1;
    ThisThread::sleep_for(1s);
    }
}