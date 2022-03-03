/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
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
        xx00 - OFF
*/

#include <cstdio>
#include <cstdlib>
#include <mbed.h>
#include <nRF24L01P.h>
#include "AnalogIn.h"
#include "HARDWARE.h"
#include "ESC.h"
#include "ThisThread.h"
#include "Thread.h"
#include "lorawan_data_structures.h"
#include <PwmOut.h>

#define TRANSFER_SIZE   10
#define DEFAULT_PIPE    0
#define CALIBRATE   0

ESC LHSMotor(LHS_MOTOR), RHSMotor(RHS_MOTOR);

// AnalogIn POT(PA_3);



float LeftMotorThrottle = 0, RightMotorThrottle = 0;

Mutex LeftMotorLock, RightMotorLock;

Thread LeftMotorThread, RightMotorThread, RadioThread;

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

char rxData[TRANSFER_SIZE];

    float POTVal = 0;

int rxDataCnt = 0;

void LeftMotorThreadMethod();
void RightMotorThreadMethod();
void RadioReceiveMethod();
float ThrottleValue(char* data);

int main() {

        wait_us(5000000);

    nRF24L01.powerUp();

// Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output power : %d dBm\n",  nRF24L01.getRfOutputPower() );
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate() );
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress() );
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress() );

    nRF24L01.setTransferSize(TRANSFER_SIZE);

    nRF24L01.setReceiveMode();

    nRF24L01.enable();

    LeftMotorThread.start(LeftMotorThreadMethod);
    RadioThread.start(RadioReceiveMethod);

    printf("WAITING...\n");

}

void RadioReceiveMethod(){
    printf("Radio Thread Started\n");
    while (true) {
        if (nRF24L01.readable()) {
            nRF24L01.read(DEFAULT_PIPE, rxData, TRANSFER_SIZE);
            printf("%s\n", rxData);
            switch (rxData[0]){
            case '1': // POT
                switch (rxData[1]){
                case '1': // Left Pitch
                    switch (rxData[2]) {
                    case '0':{ // Forwards
                        // MAKE SURE THROTTLE IS GOING FORWARDS
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        LeftMotorThrottle = ThrottleValue(&rxData[3]);
                        LeftMotorLock.unlock();
                        break;
                    }
                    case '1': // Reverse
                        // MAKE SURE THROTTLE IS GOING BACKWARDS
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        LeftMotorThrottle = ThrottleValue(&rxData[3]);
                        LeftMotorLock.unlock();
                    default:
                        break;
                    }
                case '2': // Left Roll
                    switch (rxData[2]) {
                    case '0': // Forward
                    case '1': // Reverse
                    default:
                        break;
                    }
                case '3': // Right Pitch
                    switch (rxData[2]) {
                    case '0': // Forwards
                        // MAKE SURE THROTTLE IS GOING FORWARDS
                        // set value of throttle
                        RightMotorLock.trylock_for(10ms);
                        RightMotorThrottle = ThrottleValue(&rxData[3]);
                        RightMotorLock.unlock();
                    case '1': // Reverse
                        // MAKE SURE THROTTLE IS GOING BACKWARDS
                        // set value of throttle
                    default:
                        break;
                    }
                case '4': // Right Roll
                    switch (rxData[2]) {
                    case '0': // Forwards
                        // set value of throttle 
                    case '1': // Reverse
                        // set value of throttle
                    default:
                        break;
                    }
                default:
                    break;
                }
            case '2': // BUTTON
                switch (rxData[1]) {
                case '1': // Button 1
                case '2': // Button 2
                case '3': // Button 3
                default:
                    break;
                }
                break;
            case '3': // SWITCH
                switch (rxData[2]) {
                case '1': // Switch ON
                case '2': // Switch OFF
                default:
                    break;
                }
            default:
                printf("Invalid Input\n");
            }
        }
        
    }

}

float ThrottleValue(char* data){
   float floatVal = atof(data);
   printf("%f\n", floatVal);
   return floatVal;
}

void LeftMotorThreadMethod(){

    printf("Left Motor Thread Started\n");

    LeftMotorLock.trylock_for(10ms);
    LeftMotorThrottle = 0;
    LeftMotorLock.unlock();

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff);
        LeftMotorLock.trylock_for(1ms);
        LHSMotor = LeftMotorThrottle;
        LeftMotorLock.unlock();
    }
}

void RightMotorThreadMethod(){

    printf("Right Motor Thread Started\n");

    RightMotorLock.trylock_for(10ms);
    RightMotorThrottle = 0;
    RightMotorLock.unlock();

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff);
        RightMotorLock.trylock_for(1ms);
        RHSMotor = RightMotorThrottle;
        RightMotorLock.unlock();
    }
}
