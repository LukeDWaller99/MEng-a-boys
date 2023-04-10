/**
    @file Main.cpp
    Main file for Prototyping Platform for the HEVCS - Luke Waller
**/

#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"
#include "Kernel.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include "ESC.h"
#include "mbed_wait_api.h"
#include "mecanum.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <math.h>
#include "Buzzer.h"

#define SPEED_FACTOR 10
#define FULL_THROTTLE 1.0f
#define ADJUSTED_THROTTLE 0.5f

// WHEEL ESC - OUTPUT
#define LEFT_FRONT_WHEEL PA_3
#define RIGHT_FRONT_WHEEL PF_8
#define LEFT_REAR_WHEEL PF_9
#define RIGHT_REAR_WHEEL PF_7

// JOyStickLeft - INPUT
#define X_STICK_LEFT_INPUT PF_3
#define Y_STICK_LEFT_INPUT PF_5
#define X_STICK_RIGHT_INPUT PC_0
#define Y_STICK_RIGHT_INPUT PC_3

// TRIMMING POTS FOR ADJUSTING WHEEL SPEEDS - INPUTS
#define FRONT_LEFT_TRIM_POT     PA_0
#define FRONT_RIGHT_TRIM_POT    PB_0
#define REAR_LEFT_TRIM_POT      PF_4
#define REAR_RIGHT_TRIM_POT     PC_2

// LEDS FOR FULL/HALF SPEED - OUTPUT
#define MOTOR_MODE_LED  PB_11
#define FULL_SPEED_LED  PB_10

// BUTTON FOR CHANGING FROM FULL TO HALF SPEED - INPUT
#define SPEED_ADJUST_BTN PE_15

// DRIVING MODE BUTTON/SWITCH - INPUT
#define DRIVING_MODE_BTN PE_14

// ESC TEST BUTTON
#define ESC_TEST_BUTTON PC_13

// Buzzer
#define BUZZER_OUTPUT   PE_12

ESC leftWheelFront(LEFT_FRONT_WHEEL),
    rightWheelFront(RIGHT_FRONT_WHEEL),
    leftWheelRear(LEFT_REAR_WHEEL),
    rightWheelRear(RIGHT_REAR_WHEEL);

AnalogIn xStickLeft(X_STICK_LEFT_INPUT),
         yStickLeft(Y_STICK_LEFT_INPUT),
         xStickRight(X_STICK_RIGHT_INPUT),
         yStickRight(Y_STICK_RIGHT_INPUT),
         frontLeftTrim(FRONT_LEFT_TRIM_POT),
         frontRightTrim(FRONT_RIGHT_TRIM_POT),
         rearLeftTrim(REAR_LEFT_TRIM_POT),
         rearRightTrim(REAR_RIGHT_TRIM_POT);

// DigitalIn escCalibrateButton(ESC_TEST_BUTTON);

InterruptIn speedAdjustBtn(SPEED_ADJUST_BTN),
            drivingModeBtn(DRIVING_MODE_BTN),
            escCalibrateButton(ESC_TEST_BUTTON);

DigitalOut motorModeLED(MOTOR_MODE_LED),
           fullSpeedLED(FULL_SPEED_LED);

Buzzer buzzer(BUZZER_OUTPUT);

// THREAD INITS
Thread buttonMonitor,
       LEDDriveThread,
       joyStickLeftThread,
       calibrateThread;

Mutex stickValueLock, 
      motorSpeedLock,
      speedAdjustLock,
      motorModeLock,
      speedAdjustBoolLock;

// METHOD INITS
void buttonMonitorMethod();
void LEDDriveThreadMethod();
void joyStickLeftThreadMethod();
void escCalibrateMethod();

// IRQ METHODS
void speedAdjustBtnIRQ();
void drivingModeBtnIRQ();
void calibrateRisingIRQ();
void calibrateFallingIRQ();

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
bool speedAdjustBool = false;
int motorMode = 1;


int main(){

    printf("Starting Board...\n");

    speedAdjustBtn.rise(speedAdjustBtnIRQ);
    drivingModeBtn.rise(drivingModeBtnIRQ);
    escCalibrateButton.rise(calibrateRisingIRQ);
    escCalibrateButton.fall(calibrateFallingIRQ);
    
    buttonMonitor.start(buttonMonitorMethod);
    LEDDriveThread.start(LEDDriveThreadMethod);
    joyStickLeftThread.start(joyStickLeftThreadMethod);
    calibrateThread.start(escCalibrateMethod);

}

/**

**/
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

/**

**/
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

/**

**/
void joyStickLeftThreadMethod(){
    printf("JoyStickLeft Thread Started...\n");
    while (true) {

        stickValueLock.trylock_for(1ms);

        xStickLeftValue = ((xStickLeft.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
        xStickLeftValue = (xStickLeftValue < -1.0f) || (xStickLeftValue > 1.0f) ? xStickLeftValue : 0.0f;

        yStickLeftValue = ((yStickLeft.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
        yStickLeftValue = (yStickLeftValue < -1.0f) || (yStickLeftValue > 1.0f) ? yStickLeftValue : 0.0f;

        xStickRightValue = ((xStickRight.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
        xStickRightValue = (xStickRightValue < -1.0f) || (xStickRightValue > 1.0f) ? xStickRightValue : 0.0f;

        yStickRightValue = ((yStickRight.read() * 2.0f) - 1.0f) * SPEED_FACTOR;
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
        } else if(motorMode == 2){
            leftWheelFrontSpeed = xStickLeftValue/SPEED_FACTOR * speedAdjustValue;
            rightWheelFrontSpeed = -xStickRightValue/SPEED_FACTOR * speedAdjustValue;
            leftWheelRearSpeed = -xStickLeftValue/SPEED_FACTOR * speedAdjustValue;
            rightWheelRearSpeed = xStickRightValue/SPEED_FACTOR * speedAdjustValue;
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

/**

**/
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

/**

**/
void speedAdjustBtnIRQ(){
    speedAdjustBtn.rise(NULL);
    wait_us(5000);
    if (speedAdjustBtn == 1){
        buttonMonitor.flags_set(1);
    }
    speedAdjustBtn.rise(speedAdjustBtnIRQ);
}

/**

**/
void drivingModeBtnIRQ(){
    drivingModeBtn.rise(NULL);
    wait_us(5000);
    if (drivingModeBtn == 1){
        buttonMonitor.flags_set(2);
    }
    drivingModeBtn.rise(drivingModeBtnIRQ);
}

/**

**/
void calibrateRisingIRQ(){
    escCalibrateButton.rise(NULL);
    wait_us(5000);
    if (escCalibrateButton == 1) {
        calibrateThread.flags_set(1);
    }
    escCalibrateButton.rise(calibrateRisingIRQ);
}

/**

**/
void calibrateFallingIRQ(){
    escCalibrateButton.fall(NULL);
    wait_us(5000);
    if (escCalibrateButton == 0){
        calibrateThread.flags_set(2);
    }
    escCalibrateButton.fall(calibrateFallingIRQ);
}
