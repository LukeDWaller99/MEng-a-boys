#include "DigitalIn.h"
#include "PinNames.h"
#include "mbed.h"
#include "ESC.h"
#include "mbed_wait_api.h"
#include "LCD.h"
#include "mecanum.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <math.h>

#define LEFT_FRONT_WHEEL PA_3
#define RIGHT_FRONT_WHEEL PF_8
#define LEFT_REAR_WHEEL PF_9
#define RIGHT_REAR_WHEEL PF_7
#define X_STICK_INPUT PF_3
#define Y_STICK_INPUT PF_5
#define LCD_E PD_13
#define LCD_RW PD_12
#define LCD_RS PD_11

#define PI 3.14159f
#define theta 90
#define power 10
#define turn 0
#define MULTIPLYING_FACTOR 2
#define OFFSET 1

ESC leftWheelFront(LEFT_FRONT_WHEEL),
    rightWheelFront(RIGHT_FRONT_WHEEL),
    leftWheelRear(LEFT_REAR_WHEEL),
    rightWheelRear(RIGHT_REAR_WHEEL);

AnalogIn xStick(X_STICK_INPUT);
AnalogIn yStick(Y_STICK_INPUT);

DigitalIn button(PC_13);
// LCD lcd(LCD_RS, LCD_RW, LCD_E, PD_4, PD_5, PD_6, PD_7);

// float normalisedValues(float xValue, yValue){

// }

// main() runs in its own thread in the OS
int main()
{
    printf("Starting Board...\n");
    // // lcd.put_char('H');

    float xStickValue = 0.0f;
    float yStickValue = 1.0f;
    float stickVelocity = 10.0f;
    int stickAngle = 0;
    int roundedYStick = 0;
    int roundedXStick = 0;

    stickAngle = cartToPolarAngle(xStickValue, yStickValue);
    stickVelocity = cartToPolarSpeed(xStickValue, yStickValue);
    printf("Angle: %d\n", stickAngle);
    printf("Speed: %f\n", stickVelocity);

    float leftWheelFrontSpeed = driveLeftFront(stickAngle, stickVelocity);
    float rightWheelFrontSpeed = driveRightFront(stickAngle, stickVelocity);
    float leftWheelRearSpeed = driveLeftRear(stickAngle, stickVelocity);
    float rightWheelRearSpeed = driveRightRear(stickAngle, stickVelocity);

    printf("Left Front Speed: %f\n", leftWheelFrontSpeed);
    printf("Right Front Speed: %f\n", rightWheelFrontSpeed);
    printf("Left Rear Speed: %f\n", leftWheelRearSpeed);
    printf("Right Rear Speed: %f\n", rightWheelRearSpeed);

    // xStickValue = 1.0f;
    // yStickValue = 9.0f;

    // stickAngle = cartToPolarAngle(xStickValue, yStickValue);
    // printf("Angle: %d\n", stickAngle);

    while (true) {

        if (button == 1) {
            leftWheelFront.write(-1.0f);
            rightWheelFront.write(-1.0f);
            leftWheelRear.write(-1.0f);
            rightWheelRear.write(-1.0f);
            wait_us(1000000);
            leftWheelFront.write(0.0f);
            rightWheelFront.write(0.0f);
            leftWheelRear.write(0.0f);
            rightWheelRear.write(0.0f);
            wait_us(1000000);
            leftWheelFront.write(1.0f);
            rightWheelFront.write(1.0f);
            leftWheelRear.write(1.0f);
            rightWheelRear.write(1.0f);
            wait_us(1000000);
        }
// /*
        xStickValue = ((xStick.read() * 2.0f) - 1.0f) * 10;
        xStickValue = (xStickValue < -1.0f) || (xStickValue > 1.0f) ? xStickValue : 0.0f;
        yStickValue = ((yStick.read() * 2.0f) - 1.0f) * 10;
        yStickValue = (yStickValue < -1.0f) || (yStickValue > 1.0f) ? yStickValue : 0.0f;
        printf("xStickValue: %f\n", xStickValue);
        printf("yStickValue: %f\n", yStickValue);

        stickAngle = cartToPolarAngle(xStickValue, yStickValue);
        stickVelocity = cartToPolarSpeed(xStickValue, yStickValue);
        stickVelocity = stickVelocity / 10;
        printf("Angle: %d\n", stickAngle);
        printf("Speed: %f\n", stickVelocity);


        float leftWheelFrontSpeed = driveLeftFront(stickAngle, stickVelocity);
        float rightWheelFrontSpeed = driveRightFront(stickAngle, stickVelocity);
        float leftWheelRearSpeed = driveLeftRear(stickAngle, stickVelocity);
        float rightWheelRearSpeed = driveRightRear(stickAngle, stickVelocity);

        printf("Left Front Speed: %f\n", leftWheelFrontSpeed);
        printf("Right Front Speed: %f\n", rightWheelFrontSpeed);
        printf("Left Right Speed: %f\n", leftWheelRearSpeed);
        printf("RIght Rear Speed: %f\n", rightWheelRearSpeed);

        leftWheelFront.write(leftWheelFrontSpeed);
        rightWheelFront.write(rightWheelFrontSpeed);
        leftWheelRear.write(leftWheelRearSpeed);
        rightWheelRear.write(rightWheelRearSpeed);

        wait_us(100000);
// */
    }
}
 
/* 

 Xval=analogRead(Xpin);       // Reading the value from A0
 WVx=(180./1023.)*Xval;       // Calculating the value for the X axis movement of the joystick
 
 Yval=analogRead(Ypin);       // Reading the value from A1
 WVy=(180./1023.)*Yval;       // Calculating the value for the Y axis movement of the joystick
 
 Sval=digitalRead(Spin);      // Reading the value from digital pin 2
 
 Xservo.write(WVx);           // Moving the servo using the X-movement of the joystick
 Yservo.write(WVy);           // Moving the servo using the Y-movement of the joystick
 
 delay(dt);
*/