/**
    @file Main.cpp
    Main debugging file for controller board Final Year Project - Luke Waller
**/
#include <mbed.h>
#include <DigitalIn.h>
#include <DigitalOut.h>
#include <ThisThread.h>

#include "Buzzer.h"
#include "HARDWARE.h"

DigitalIn BT1(BTN1), BT2(BTN2), BT3(BTN3), SW_1(SW1);        
DigitalOut LED(LED_1);                                             
AnalogIn L_Pitch(L_PITCH), L_Roll(L_ROLL), R_Pitch(R_PITCH), R_Roll(R_ROLL);   
Buzzer buzzer(BUZZER);

Thread btnThread, swThread, potThread; // creating threads

Mutex potMutex; // creating mutex lock for pots

void potMethod();
void btnMethod();
void swMethod();

int main() {

    printf("Starting Board...\n");

    buzzer.chime();

    // starting Threads
    potThread.start(potMethod);
    btnThread.start(btnMethod);
    swThread.start(swMethod);

}

void swMethod(){
    while (true) {
        LED = SW_1 == 1 ? 1 : 0;
    }
}

void btnMethod(){
    while (true) {
        buzzer = BT1 == 1 || BT2 == 1 || BT3 == 1 ? 1 : 0;
    }
}

void potMethod(){

    float leftPitch, rightPitch, leftRoll, rightRoll;

    while (true) {
        potMutex.lock();
        leftPitch = L_Pitch.read();
        rightPitch = R_Pitch.read();
        leftRoll = L_Roll.read();
        rightRoll = R_Roll.read();
        potMutex.unlock();

        printf("%c",char(27));  // ESC
        printf("[2J");          // clear screen
        printf("%c",char(27));  // ESC
        printf("[H");           // cursor to home

        printf("-----------------------\n");
        printf("Left Pitch: %f\n", leftPitch);
        printf("Right Pitch: %f\n", rightPitch);
        printf("Left Roll: %f\n", leftRoll);
        printf("Right Roll: %f\n", rightRoll);   
        printf("-----------------------\n");

        ThisThread::sleep_for(200ms);     

    }

}
