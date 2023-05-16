/**
    @file Main.cpp
    Main file for Prototyping Platform for the HEVCS - Luke Waller
**/

#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"
#include "Kernel.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include "ESC.h"
#include "Servo.h"
#include "mbed_wait_api.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <math.h>


#define SPEED_FACTOR 10
#define FULL_THROTTLE 1.0f
#define ADJUSTED_THROTTLE 0.5f

// DEBUG LEDs
#define DEBUG_LED_1 PE_12
#define DEBUG_LED_2 PE_14
#define DEBUG_LED_3 PE_15

// COLLISION LEDs
#define COLLISION_LED_1 PF_12
#define COLLISION_LED_2 PF_13
#define COLLISION_LED_3 PE_9
#define COLLISION_LED_4 PE_11
#define COLLISION_LED_5 PF_14
#define COLLISION_LED_6 PE_13
#define COLLISION_LED_7 PF_15
#define COLLISION_LED_8 PG_14

// SOLENOIDS
#define SOL_1 PG_9
#define SOL_2 PE_7
#define SOL_3 PE_8
#define SOL_4 PE_10

// VESCs
#define LEFT_FRONT_WHEEL PA_3 // VESC 1
#define RIGHT_FRONT_WHEEL PC_8 // VESC 2
#define LEFT_REAR_WHEEL PC_9 // VESC 3
#define RIGHT_REAR_WHEEL PB_4 // VESC 4

// CONNECTOR CONNECTION
#define CONN_CONNECTOR PF_10

// RELAYS
#define RELAY_1 PF_2
#define RELAY_2 PD_0
#define RELAY_3 PD_1
#define RELAY_4 PG_0

// SERVOs
#define SERVO_1 PB_1 // SERVO 1
#define SERVO_2 PB_6 // SERVO 2
#define SERVO_3 PD_13 // SERVO 3
#define SERVO_4 PD_12 // SERVO 4

// BATTERY LEVEL MONITORS
#define BAT_LEV_1 PB_2
#define BAT_LEV_2 PD_11
#define BAT_LEV_3 PA_0
#define BAT_LEV_4 PE_0

// SWITCHES
#define SW_1_UP PC_10
#define SW_1_DW PC_11
#define SW_2_UP PG_2
#define SW_2_DW PG_3
#define SW_3_UP PC_11
#define SW_3_DW PD_2

// BUTTONS
#define BTN_1 PD_7
#define BTN_2 PC_0
#define BTN_3 PD_6
#define BTN_4 PD_3
#define BTN_5 PD_4
#define BTN_6 PD_5

// CONTROLLER BUTTONS
// #define C_BTN_1 PF_7
// #define C_BTN_2 PF_8
// #define C_BTN_3 PA_4

//SPEED TRIM POTS
// #define TRIM_1 PA_4
#define TRIM_2 PA_5
#define TRIM_3 PA_6
#define TRIM_4 PA_7

// JOyStickLeft - INPUT
#define X_STICK_LEFT_INPUT PF_3
#define Y_STICK_LEFT_INPUT PF_5
#define X_STICK_RIGHT_INPUT PF_8
#define Y_STICK_RIGHT_INPUT PF_7

ESC leftWheelFront(LEFT_FRONT_WHEEL),
    rightWheelFront(RIGHT_FRONT_WHEEL),
    leftWheelRear(LEFT_REAR_WHEEL),
    rightWheelRear(RIGHT_REAR_WHEEL);

Servo servo1(SERVO_1),
      servo2(SERVO_2),
      servo3(SERVO_3),
      servo4(SERVO_4);

AnalogIn xStickLeft(X_STICK_LEFT_INPUT),
         yStickLeft(Y_STICK_LEFT_INPUT),
         xStickRight(X_STICK_RIGHT_INPUT),
         yStickRight(Y_STICK_RIGHT_INPUT);

InterruptIn connConnector(CONN_CONNECTOR);

// DigitalIn cBtn1(C_BTN_1),
//           cBtn2(C_BTN_2),
//           cBtn3(C_BTN_3);


BusOut  cLEDs(COLLISION_LED_1, COLLISION_LED_2, COLLISION_LED_3, COLLISION_LED_4,
              COLLISION_LED_5, COLLISION_LED_6, COLLISION_LED_7, COLLISION_LED_8),
        solenoid(SOL_1, SOL_2, SOL_3, SOL_4),
        relays(RELAY_1, RELAY_2, RELAY_3, RELAY_4);

DigitalOut dLED1(DEBUG_LED_1), 
           dLED2(DEBUG_LED_2),
           dLED3(DEBUG_LED_3);

// THREAD INITS
Thread buttonMonitor,
       joyStickLeftThread,
       calibrateThread,
       connThread;

Mutex stickValueLock, 
      motorSpeedLock,
      speedAdjustLock,
      motorModeLock,
      speedAdjustBoolLock;

Ticker LEDAliveTicker;

// METHOD INITS
void buttonMonitorMethod();
void LEDDriveThreadMethod();
void joyStickLeftThreadMethod();
void escCalibrateMethod();
void LEDAliveIRQ();
void connInIRQ();
void connOutIRQ();
void connThreadMethod();

// IRQ METHODS
void speedAdjustBtnIRQ();
void drivingModeBtnIRQ();
void calibrateRisingIRQ();
void calibrateFallingIRQ();
void cBtn1FallingIRQ();

// varaible initialisation
float xStickLeftValue = 0.0f;
float yStickLeftValue = 0.0f;
float xStickRightValue = 0.0f;
float yStickRightValue = 0.0f;
float leftWheelFrontSpeed = 0.0f;
float rightWheelFrontSpeed = 0.0f;
float leftWheelRearSpeed = 0.0f;
float rightWheelRearSpeed = 0.0f;
float speedAdjustValue = FULL_THROTTLE;
int motorMode = 1;


int main(){

    printf("Starting Board...\n");
    cLEDs = 1;
    wait_us(250000);
    cLEDs = 2;
    wait_us(250000);
    cLEDs = 4;
    wait_us(250000);
    cLEDs = 8;
    wait_us(250000);
    cLEDs = 16;
    wait_us(250000);
    cLEDs = 32;
    wait_us(250000);
    cLEDs = 64;
    wait_us(250000);
    cLEDs = 128;
    wait_us(250000);
    cLEDs = 0;


    // servo1 = 1.0f;
    // servo2 = 1.0f;
    // servo3 = 1.0f;
    // servo4 = 1.0f;



    joyStickLeftThread.start(joyStickLeftThreadMethod);
    LEDAliveTicker.attach(LEDAliveIRQ, 1s);
    // connThread.start(connThreadMethod);
    // connConnector.rise(connInIRQ);
    // connConnector.fall(connOutIRQ);


     while (true) {
        
    // printf("Left X : %f\n", xStickLeft.read());
    // printf("Left Y : %f\n", yStickLeft.read());
    // wait_us(1000000);
     }
}

/**

**/
/*
void buttonMonitorMethod(){
    printf("Button Monitor Thread Started...\n");
    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        printf("Flag = %d\n", flag);
        switch (flag) {
        case 1: // button 1 - Speed Adjust Button
            printf("Speed Adjust Button Pressed\n");
            speedAdjustLock.trylock_until(Kernel::Clock::now() + 1s);
            if(speedAdjustBool == true){
                speedAdjustBool = false;
                speedAdjustValue = ADJUSTED_THROTTLE;
                printf("Adjusted Throttle: %f", speedAdjustValue);
                LEDDriveThread.flags_set(1);
            } else {
                speedAdjustBool = true;
                speedAdjustValue = FULL_THROTTLE;
                printf("Adjusted Throttle: %f", speedAdjustValue);
                LEDDriveThread.flags_set(2);
            }
            speedAdjustLock.unlock();
            break;
        case 2: // button 2 - Motor Mode
            printf("Motor Mode Button Pressed\n");
            motorModeLock.trylock_for(1ms);
            if (motorMode == 1) {
                motorMode = 2;
                LEDDriveThread.flags_set(4);
            } else {
                motorMode = 1;
                LEDDriveThread.flags_set(8);
            }
            motorModeLock.unlock();
            break;
        default:
            break;
        }
    }
}
*/

/**

**/
/*
void LEDDriveThreadMethod(){
    printf("LED Drive Thread Started...\n");
    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        printf("Flag = %d\n", flag);
        switch (flag) {
        case 1:
            fullSpeedLED = 1;
            break;
        case 2:
            fullSpeedLED = 0;
            break;
        case 4:
            motorModeLED = 1;
            break;
        case 8:
            motorModeLED = 0;
            break;
        }
    }
}
*/

/**

**/

void joyStickLeftThreadMethod(){
    printf("JoyStickLeft Thread Started...\n");
    while (true) {

        stickValueLock.trylock_for(1ms);

        xStickLeftValue = ((xStickLeft.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
         printf("Left X : %f\n", xStickLeft.read());
        xStickLeftValue = (xStickLeftValue < -1.0f) || (xStickLeftValue > 1.0f) ? xStickLeftValue : 0.0f;

        yStickLeftValue = ((yStickLeft.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
         printf("Left Y : %f\n", yStickLeft.read());
        yStickLeftValue = (yStickLeftValue < -1.0f) || (yStickLeftValue > 1.0f) ? yStickLeftValue : 0.0f;

        xStickRightValue = ((xStickRight.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
        // printf("Right X : %f\n", xStickRight.read());
        xStickRightValue = (xStickRightValue < -1.0f) || (xStickRightValue > 1.0f) ? xStickRightValue : 0.0f;

        yStickRightValue = ((yStickRight.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
        // printf("Right y : %f\n", yStickRight.read());
        yStickRightValue = (yStickRightValue < -1.0f) || (yStickRightValue > 1.0f) ? yStickRightValue : 0.0f;

        stickValueLock.unlock();

        motorModeLock.trylock_for(1ms);
        motorSpeedLock.trylock_for(1ms);
        speedAdjustLock.trylock_for(1ms);
        if (motorMode == 1){
            leftWheelFrontSpeed = ((xStickLeftValue + yStickLeftValue)/SPEED_FACTOR) * speedAdjustValue;
            rightWheelFrontSpeed = ((xStickLeftValue - yStickLeftValue)/SPEED_FACTOR) * speedAdjustValue;
            leftWheelRearSpeed = ((xStickLeftValue - yStickLeftValue)/SPEED_FACTOR) * speedAdjustValue;
            rightWheelRearSpeed = ((xStickLeftValue + yStickLeftValue)/SPEED_FACTOR) * speedAdjustValue;
        }

        leftWheelFront.write(leftWheelFrontSpeed);
        rightWheelFront.write(rightWheelFrontSpeed);
        leftWheelRear.write(leftWheelRearSpeed);
        rightWheelRear.write(rightWheelRearSpeed);
        motorSpeedLock.unlock();
        motorModeLock.unlock();
        speedAdjustLock.unlock();
    }
}

void LEDAliveIRQ(){
    dLED1 = !dLED1;
}

void connInIRQ(){
    dLED3 = 0;
    connConnector.rise(NULL);
    calibrateThread.flags_set(2);
    connConnector.rise(connInIRQ);
}

void connOutIRQ(){
    dLED3 = 1;
    connConnector.fall(NULL);
    calibrateThread.flags_set(1);
    connConnector.fall(connOutIRQ);
}

void connThreadMethod(){
    printf("Connector Thread Started...\n");
    while(true){
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        switch(flag){
            case '1':
                motorSpeedLock.lock();
                leftWheelFront.write(0.0f);
                rightWheelFront.write(0.0f);
                leftWheelRear.write(0.0f);
                rightWheelRear.write(0.0f);
            break;
            case '2':
                motorSpeedLock.unlock();
            break;
            default : 
            break;
        }
    }
}

/**

**/
/*
void escCalibrateMethod(){
    printf("Calibrate ESC Thread Started\n");
    while(true){
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        bool calibrateTesting = (flag == 1) ? true : false;
        ThisThread::flags_clear(0x7fffffff);
        while(calibrateTesting == true){
            // ESC minimum values 
            leftWheelFront.write(-1.0f);
            rightWheelFront.write(-1.0f);
            leftWheelRear.write(-1.0f);
            rightWheelRear.write(-1.0f);
            wait_us(1000000);
            // ESC mid values
            leftWheelFront.write(0.0f);
            rightWheelFront.write(0.0f);
            leftWheelRear.write(0.0f);
            rightWheelRear.write(0.0f);
            wait_us(1000000);
            // ESC max values
            leftWheelFront.write(1.0f);
            rightWheelFront.write(1.0f);
            leftWheelRear.write(1.0f);
            rightWheelRear.write(1.0f);
            wait_us(1000000);
            flag = ThisThread::flags_get();
            printf("Flag = %d\n", flag);
            calibrateTesting = (flag == 2) ? false : true;
            ThisThread::flags_clear(2);
        }
    }
}
*/
/**

**/
/*
void calibrateRisingIRQ(){
    escCalibrateButton.rise(NULL);
    wait_us(5000);
    if (escCalibrateButton == 1) {
        calibrateThread.flags_set(1);
    }
    escCalibrateButton.rise(calibrateRisingIRQ);
}
*/
/**

**/
/*
void calibrateFallingIRQ(){
    escCalibrateButton.fall(NULL);
    wait_us(5000);
    if (escCalibrateButton == 0){
        calibrateThread.flags_set(2);
    }
    escCalibrateButton.fall(calibrateFallingIRQ);
}
*/