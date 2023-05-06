#include <mbed.h>
#include "F429ZI_Hardware.h"
#include <ThisThread.h>
#include <rtos.h>
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"

//Onboard Peripherals 
//InterruptIn USER_BTN(USR_BTN);
DigitalOut USER_GREEN(USER_LED_GREEN);
DigitalOut USER_RED(USER_LED_RED);
DigitalOut USER_BLUE(USER_LED_BLUE);

InterruptIn SW_1(SWITCH_1);
InterruptIn SW_2(SWITCH_2);
//DigitalIn USER_BTN(USR_BTN);
InterruptIn SW_ASCEND(ASCEND);
InterruptIn SW_DESCEND(DESCEND);
InterruptIn SW_LIGHTS(LIGHTS);
InterruptIn SW_BRAKE(BRAKE_MODE);
InterruptIn SW_REV(REV_MODE);
InterruptIn SW_M_MODE_1(MOTOR_MODE_1);
InterruptIn SW_M_MODE_2(MOTOR_MODE_2);
InterruptIn SW_M_EN(MOTOR_EN);
InterruptIn SW_M_DE(MOTOR_DE);

DigitalOut SW_1_LED(SWITCH_1_LED);
DigitalOut SW_2_LED(SWITCH_2_LED);
DigitalOut M_MODE_1_LED(MOTOR_MODE_1_LED);
DigitalOut M_MODE_2_LED(MOTOR_MODE_2_LED);
DigitalOut Lights_LED(LIGHTS_LED);
DigitalOut M_EN_LED(EN_LED);
DigitalOut M_DE_LED(DE_LED);

Thread inputMonitor;
Thread switchMonitor;

#define BLINKING_RATE 500ms

void switchMonitorMethod();
void switchDetection();
void SW_1_IRQ(); 
void SW_2_IRQ(); 
void ASC_IRQ(); 
void DESC_IRQ(); 
//void M_MODE_1_IRQ(); 
//void M_MODE_2_IRQ(); 
//void LIGHTS_IRQ(); 

int main()
{
   
	printf("Starting Board...\n");
    //detect rise and fall
    //switchDetection();
    //switchMonitor.start(switchMonitorMethod);

    while (true){

    }   
}

void SW_1_IRQ(){
    SW_1.rise(NULL);
    SW_2.fall(NULL);
    wait_us(5000);
    if (SW_1 == 1) {
        switchMonitor.flags_set(11);
    }  
    if (SW_1 == 0){
        switchMonitor.flags_set(10);
    }
    SW_1.rise(SW_1_IRQ);
    SW_1.fall(SW_1_IRQ);
}

void SW_2_IRQ(){
    SW_2.rise(NULL);
    wait_us(5000);
    if (SW_2 == 1) {
        switchMonitor.flags_set(12);
    }
    SW_2.rise(SW_2_IRQ);
}

void ASC_IRQ(){

}

void DESC_IRQ(){

}



void switchDetection(){
    SW_1.rise(SW_1_IRQ);
    SW_2.fall(SW_1_IRQ);
    SW_2.rise(SW_2_IRQ);
    SW_2.fall(SW_2_IRQ);
    // SW_ASCEND.rise(ASC_IRQ);
    // SW_ASCEND.fall(ASC_IRQ);
    // SW_DESCEND.rise(DESC_IRQ);
    // SW_DESCEND.fall(DESC_IRQ);
    //SW_M_MODE_1.rise(M_MODE_1_IRQ);
    // SW_M_MODE_1.fall(M_MODE_1_IRQ);
    // SW_M_MODE_2.rise(M_MODE_2_IRQ);
    // SW_M_MODE_2.fall(M_MODE_2_IRQ);
    // SW_LIGHTS.rise(LIGHTS_IRQ);
    // SW_LIGHTS.fall(LIGHTS_IRQ);
}

void switchMonitorMethod(){
    printf("Switch Monitoring Thread Started...\n");
    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);

        switch (flag) {
            case 11: 
            printf("SW 1 Activated\n");
            SW_1_LED = 1;
            break;

            case 10:
            printf("SW 1 Deactivated\n");
            SW_1_LED = 0;
            break;

            case 21:
            printf("SW 2 Activated\n");
            SW_2_LED = 1;
            break;

            case 20:
            printf("SW 2 Deactivated\n");
            SW_2_LED = 0;
            break;

            // case 31:
            // printf("Ascend Switch Activated");
            // break;


        }
    }
}