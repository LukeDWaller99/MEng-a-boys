/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
**/

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

    // RightMotorThread.start(RightMotorThreadMethod);


    // while (true) {
    //     // POTVal = POT.read();
    //     // printf("%f\n", POTVal);
    //     // LHSMotor = POTVal;
    // }



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



    // while (true) {
    // if (nRF24L01.readable(DEFAULT_PIPE)) {
    //         rxDataCnt = nRF24L01.read(DEFAULT_PIPE, rxData, TRANSFER_SIZE);
    //         printf("%s\n", rxData);
    //     }
    // }

}

void RadioReceiveMethod(){
    printf("Radio Thread Started\n");
    while (true) {
        if (nRF24L01.readable()) {
            nRF24L01.read(DEFAULT_PIPE, rxData, TRANSFER_SIZE);
            printf("%s\n", rxData);
            switch (rxData[0]){
            case 'B':
                printf("Button\n");
                switch (rxData[2]) {
                case '1':
                    printf("1\n");
                    LHSMotor = 1;
                    LHSMotor = 0;
                    break;
                case '2':
                    printf("2\n");
                    break;
                case '3':
                    printf("3\n");
                    break;
                default:
                    break;
                }
                break;
            case 'S':
                switch (rxData[3]) {
                case '1':
                    break;
                case '0':
                    break;
                default:
                    break;
                }
                break;
            case 'L':
                switch (rxData[1]) {
                case 'P':
                    // left throttle
                    // LeftMotorLock.trylock_for(10ms);
                    ThrottleValue(rxData);
                    // LeftMotorLock.unlock();
                    break;
                case 'R':
                    break;
                default:
                    break;
                }
                break;
            case 'R':
                switch (rxData[1]) {
                case 'P':
                    // right throttle
                    break;
                case 'R':
                    break;
                default:
                    break;
                }
                break;
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
        // ThisThread::flags_wait_any(0x7fffffff);
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
        // RightMotorThrottle = whatever the value is /10
        RHSMotor = RightMotorThrottle;
        RightMotorLock.unlock();
    }
}
