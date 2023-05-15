/**
    @file Main.cpp
    Main file for the Platform for the HEVCS
**/

#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"
#include "Kernel.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "mbed-os/drivers/include/drivers/BusOut.h"
#include "mbed.h"
#include "ESC.h"
// #include "mbed_wait_api.h"
// #include "mecanum.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <math.h>
#include "Buzzer.h"
#include "Servo.h"
#include "Mask.h"

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
#define SOL_1   PG_9
#define SOL_2   PE_7
#define SOL_3   PE_8
#define SOL_4   PE_10

// VESCs
#define VESC_1  PA_3
#define VESC_2  PC_8
#define VESC_3  PC_9
#define VESC_4  PB_4

// CONNECTOR CONNECTION
#define CONN_CONNECTOR  PF_10

// RELAYS
#define RELAY_1 PF_2
#define RELAY_2 PD_0
#define RELAY_3 PD_1
#define RELAY_4 PG_0

// SERVOs
#define SERVO_1 PB_1
#define SERVO_2 PB_6
#define SERVO_3 PD_14
#define SERVO_4 PD_12

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

//SPEED TRIM POTS
// #define TRIM_1 PA_4
#define TRIM_2 PA_5
#define TRIM_3 PA_6
#define TRIM_4 PA_7

// BusOut  dLEDs(DEBUG_LED_1, DEBUG_LED_2, DEBUG_LED_3),
//         cLEDs(COLLISION_LED_1, COLLISION_LED_2, COLLISION_LED_3, COLLISION_LED_4,
//               COLLISION_LED_5, COLLISION_LED_6, COLLISION_LED_7, COLLISION_LED_8),
//         solenoid(SOL_1, SOL_2, SOL_3, SOL_4),
//         relays(RELAY_1, RELAY_2, RELAY_3, RELAY_4);

// AnalogIn frontLeftTrim(TRIM_1),
        //  frontRightTrim(TRIM_2),
        //  rearLeftTrim(TRIM_3),
        //  rearRightTrim(TRIM_4);

ESC frontLeftESC(VESC_1),
    frontRightESC(VESC_2),
    rearLeftESC(VESC_3),
    rearRightESC(VESC_4);

// Servo frontLeftServo(SERVO_1),
//         frontRightServo(SERVO_2),
//         rearLeftServo(SERVO_3),
//         rearRightServo(SERVO_4);

DigitalIn connectorCon(CONN_CONNECTOR);

DigitalIn sw1Up(SW_1_UP), sw1Down(SW_1_DW),
          sw2Up(SW_2_UP), sw2Down(SW_2_DW),
          sw3Up(SW_3_UP), sw3Down(SW_3_DW);

DigitalIn btn1(BTN_1), btn2(BTN_2), btn3(BTN_3),
          btn4(BTN_4), btn5(BTN_5), btn6(BTN_6);

SPISlave myspi(PB_5, PB_4, PB_3, PA_4); //mosi, miso, sck, cs

Thread SPIThread;

void SPIReadMethod();

int main(){

    printf("Starting Board...\n");

    myspi.format(8,0);
    myspi.frequency(1000000);
    myspi.reply(0x00); 

    int dataIn = 0;

    SPIThread.start(SPIReadMethod);

    // while(true){

    // }

/*
        dLEDs=0;

        if(sw1Up == 1){
            dLEDs = 1;
            frontLeftESC.write(-1.0f);
            frontRightESC.write(-1.0f);
            rearLeftESC.write(-1.0f);
            rearRightESC.write(-1.0f);
            wait_us(1000000);
            // ESC mid values
            frontLeftESC.write(0.0f);
            frontRightESC.write(0.0f);
            rearLeftESC.write(0.0f);
            rearRightESC.write(0.0f);
            wait_us(1000000);
            // ESC max values
            frontLeftESC.write(1.0f);
            frontRightESC.write(1.0f);
            rearLeftESC.write(1.0f);
            rearRightESC.write(1.0f);
            wait_us(1000000);
        }
    }*/
}

void SPIReadMethod(){
    printf("SPI Read Method Started...\n");
    while (true) {

        int input = 0;

        // printf("Running\n");

        if(myspi.receive()){
        input = myspi.read();
        myspi.reply(input);
        printf("SPI In: %d\n", input);

        int dataOutput = 0;
        int shiftedInput = 0;
        int shiftedInputType = 0;
        int dataInput = 0;
        int stickValue = 0;
/*
    // shiftedInputType = input >> 6;
    // shiftedInput = input >> 4;
    dataInput = input & dataMask;
    // std::cout << "Input: " << input << std::endl;
    // std::cout << "Joystick 1 Mask: " << joyMask1 << std::endl;
    // std::cout << "Joystick 2 Mask: " << joyMask2 << std::endl;
    // std::cout << "Input Type No: " << shiftedInputType << std::endl;
    // std::cout << "Input Shifted: " << shiftedInput << std::endl;
    // std::cout << "Data Input: " << dataInput << std::endl;
  
  switch(shiftedInputType){
      case joystickMask:
            if((8 < dataInput) && (dataInput <= 16)){
                dataOutput = input & speedMask;
                dataOutput = -dataOutput;
                printf("Negative Speed: %d\n", dataOutput);
            } else if ((0 <= dataInput) && (dataInput <= 7)){
                dataOutput = input & speedMask;
                printf("Positive Speed: %d\n", dataOutput);
            } else {}
            switch(shiftedInput){
            case joyMask1:
            printf("It is Stick 1\n");
            break;
            case joyMask2:
            printf("It is Stick 2\n");
            break;
            case joyMask3:
            printf("It is Stick 3\n");
            break;
            case joyMask4:
            printf("It is Stick 4\n");
            break;
          }
      break;
      case switchMask:
    //   std::cout << "It is a switch" << std::endl;
      break;
      case ledMask:
    //   std::cout << "It is an LED" << std::endl;
      break;
      case servoMask:
    //   std::cout << "It is a servo" << std::endl;
      break;

*/
    // }
        }
    }
}

// 0b00aabccc
// 0b00001000 - joystick 1 forward

// if transmission and bitmask are 1 then it is that
// 0b00001000 - forwards
// 0b00000000 - reverse
// 0b00000000 - joystick 1x
// 0b00010000 - joystick 1y
// 0b00100000 - joystick 2x
// 0b00110000 - joystick 2y
// then look at data bits
// if((input>>6) == 0){ // checking if for joysticks
//      if(input & 0b00000000){ // joystick 1
// else if (input & 0b00010000){ // joystick 2
// else if (input & 0b00100000) // joystick 3
// else if (input & 0b00110000) // joystick 4
// }

// 0b01000000 - sw1 off 
// 0b01000001 - sw1 on
// 0b01000010 - sw2 off
// 0b01000011 - sw2 on
// 0b01000100 - sw3 off
// 0b01000101 - sw3 on
// 0b01000110 - sw4 off
// 0b01000111 - sw4 on
// 0b01001000 - sw5 off
// 0b01001001 - sw5 on
// 0b01001010 - sw6 off
// 0b01001011 - sw6 on
// 0b01001100 - sw7 off
// 0b01001101 - sw7 on
// 0b01001110 - sw8 off
// 0b01001111 - sw8 on
// 0b01010000 - sw9 off
// 0b01010001 - sw9 on
// 0b01010010 - sw10 off
// 0b01010011 - sw10 on

// 0b10000000 - led 1
// 0b10000001 - led 2
// 0b10000010 - led 2
// 0b10000011 - led 3
// 0b10000100 - led 4
// 0b10000101 - led 5
// 0b10000110 - led 6
// 0b10000111 - led 7

// for the leds
// if((input << 6) == 2){
//      if(input > 8){
//          
//      }
//    cLeds = input >> 1;
// }

/*
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


void speedAdjustBtnIRQ(){
    speedAdjustBtn.rise(NULL);
    wait_us(5000);
    if (speedAdjustBtn == 1){
        buttonMonitor.flags_set(1);
    }
    speedAdjustBtn.rise(speedAdjustBtnIRQ);
}

// SPI DECODING CODE



*/