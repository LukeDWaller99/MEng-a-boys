/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
**/

#include <cstdio>
#include <cstdlib>
#include <mbed.h>
#include <nRF24L01P.h>
#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "HARDWARE.h"
#include "ESC.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "Thread.h"
#include <PwmOut.h>
#include "L298N.h"
#include "Buzzer.h"
#include "TRANSMISSION_CODES.h"

#define TRANSFER_SIZE   5
#define DEFAULT_PIPE    0
#define CALIBRATE       0
#define MOTOR_OFF       0.0f
#define MOTOR_ON        1.0f

ESC FWDLeftMotor(FWD_LHS_MOTOR), 
    FWDRightMotor(FWD_RHS_MOTOR),
    REVLeftMotor(REV_LHS_MOTOR),
    REVRightMotor(REV_RHS_MOTOR);

L298N ConvMotor1(CONV_MOTOR_1_A, CONV_MOTOR_1_B, CONV_MOTOR_1_ENABLE),
      ConvMotor2(CONV_MOTOR_2_A, CONV_MOTOR_2_B, CONV_MOTOR_2_ENABLE);

DigitalIn BT1(BTN_1), BT2(BTN_2), SW1(SW_1), SW2(SW_2), SW3(SW_3), SW4(SW_4), SW5(SW_5), SW6(SW_6);

DigitalIn Sensor_1(IR_1), Sensor_2(IR_2), Sensor_3(IR_3), Sensor_4(IR_4);

DigitalOut led(LED_1);

Buzzer Buzz(BUZZER);

BusOut LEDs(LED_1, LED_10, LED_9, LED_8, LED_7, LED_6, LED_5, LED_4, LED_3, LED_2);

float fwdLeftMotorThrottle = 0, fwdRightMotorThrottle = 0;
float revLeftMotorThrottle = 0, revRightMotorThrottle = 0;

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

int main() {

    printf("Starting Board...\n");

    wait_us(5000000);

    nRF24L01.powerUp();

//  Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output power : %d dBm\n",  nRF24L01.getRfOutputPower() );
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate() );
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress() );
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress() );

    nRF24L01.setTransferSize(TRANSFER_SIZE);

//     nRF24L01.setReceiveMode();

//     nRF24L01.enable();

    LEDs = 0;
    Buzz = 0;

while(true){
    if (BT1 == 1){
        if (SW3 == 1){LEDs = 31;}
        else {LEDs = 992;}
    }
    else {LEDs = 0;}

    if (BT2 == 1){FWDLeftMotor = 1.0f, FWDRightMotor = 1.0f, 
                  REVLeftMotor = 1.0f, REVRightMotor = 1.0f;}
    else {FWDLeftMotor = 0.0f, FWDRightMotor = 0.0f,
          REVLeftMotor = 0.0f, REVLeftMotor = 0.0f;}

    if (SW1 == 1){Buzz = 1;}
    else if(SW2 == 1){Buzz = 0;}

    if (SW4 == 1){ConvMotor1 = 1, ConvMotor2 = 1;} // Conv Motors forwards
    else if (SW5 == 1){ConvMotor1 = -1, ConvMotor2 = -1;} // conv motors reverse

    if (SW6 == 1){ConvMotor1 = true, ConvMotor2 = true;} // enable motors
    else {ConvMotor1 = false, ConvMotor2 = false;} // disable motors
    }
}
