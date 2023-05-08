#include <mbed.h>
#include "F429ZI_Hardware.h"
#include <ThisThread.h>
#include <rtos.h>
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "InterruptIn.h"

// SPI spi(MOSI_1, MISO_1, CLK_1);
// DigitalOut CS(CS_1);

//Onboard Peripherals 
//InterruptIn USER_BTN(USR_BTN);
DigitalOut USER_GREEN(USER_LED_GREEN);
DigitalOut USER_RED(USER_LED_RED);
DigitalOut USER_BLUE(USER_LED_BLUE);

InterruptIn SW_1(SWITCH_1);
InterruptIn SW_2(SWITCH_2);
InterruptIn SW_ASCEND(ASCEND);
InterruptIn SW_DESCEND(DESCEND);
InterruptIn SW_LIGHTS(LIGHTS);
InterruptIn SW_BRAKE(BRAKE_MODE);
InterruptIn SW_REV(REV_MODE);
//InterruptIn SW_M_MODE_1(MOTOR_MODE_1);
//InterruptIn SW_M_MODE_2(MOTOR_MODE_2);
InterruptIn SW_M_EN(MOTOR_EN);
InterruptIn SW_M_DE(MOTOR_DE);

DigitalOut SW_1_LED(SWITCH_1_LED);
DigitalOut SW_2_LED(SWITCH_2_LED);
DigitalOut SW_ASC_LED(ASCEND_LED);
DigitalOut SW_DESC_LED(DESCEND_LED);
DigitalOut M_MODE_1_LED(MOTOR_MODE_1_LED);
DigitalOut M_MODE_2_LED(MOTOR_MODE_2_LED);
DigitalOut SW_BRAKE_LED(BRAKE_LED);
DigitalOut SW_REV_LED(REV_LED);
DigitalOut SW_KILL_LED(KILL_LED);
DigitalOut SW_LIGHTS_LED(LIGHTS_LED);
DigitalOut SW_M_EN_LED(EN_LED);
DigitalOut SW_M_DE_LED(DE_LED);

Thread switchMonitor;

void switchMonitorMethod();
void switchDetection();
void SW_1_IRQ(); 
void SW_2_IRQ(); 
void SW_ASC_IRQ(); 
void SW_DESC_IRQ(); 
// void SW_MODE_1_IRQ(); 
// void SW_MODE_2_IRQ(); 
void SW_LIGHTS_IRQ();
void SW_BRAKE_IRQ();
void SW_REV_IRQ();
void SW_M_EN_IRQ();
void SW_M_DE_IRQ(); 

int main()
{   
    printf("Starting Board...\n");

    // //SPI BUSINESS
    // CS = 1; //deselect
    // spi.format(8, 3); //8-bit data
    // spi.frequency(1000000); //1MHz CLK
	// CS = 0; //select
    // spi.write(0x8F); //WhoAmI
    // int whoami= spi.write(0x00);
    // printf("WhoAmI: 0x%X\n", whoami);

    //SWITCHY BUSINESS
    switchDetection();
    switchMonitor.start(switchMonitorMethod);

    while (true){

    }   
}

void SW_1_IRQ(){
    SW_1.rise(NULL);
    SW_1.fall(NULL);
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
    SW_2.fall(NULL);
    wait_us(5000);
    if (SW_2 == 1) {
        switchMonitor.flags_set(21);
    }
    if (SW_2 == 0) {
        switchMonitor.flags_set(20);
    }
    SW_2.rise(SW_2_IRQ);
    SW_2.fall(SW_2_IRQ);
}

void SW_ASC_IRQ(){
    SW_ASCEND.rise(NULL);
    SW_ASCEND.fall(NULL);
    wait_us(5000);
    if (SW_2 == 1){
        switchMonitor.flags_set(31);
    }
    if (SW_2 == 0){
        switchMonitor.flags_set(30);
    }
    SW_ASCEND.rise(SW_ASC_IRQ);
    SW_ASCEND.fall(SW_ASC_IRQ);
}

void SW_DESC_IRQ(){
    SW_DESCEND.rise(NULL);
    SW_DESCEND.fall(NULL);
    wait_us(5000);
    if (SW_2 == 1){
        switchMonitor.flags_set(41);
    }
    if (SW_2 == 0){
        switchMonitor.flags_set(40);
    }
    SW_DESCEND.rise(SW_DESC_IRQ);
    SW_DESCEND.fall(SW_DESC_IRQ);
}

void SW_LIGHTS_IRQ(){
    SW_LIGHTS.rise(NULL);
    SW_LIGHTS.fall(NULL);
    wait_us(5000);
    if (SW_LIGHTS == 1){
        switchMonitor.flags_set(51);
    }
    if (SW_LIGHTS == 0){
        switchMonitor.flags_set(50);
    }
    SW_LIGHTS.rise(SW_LIGHTS_IRQ);
    SW_LIGHTS.fall(SW_LIGHTS_IRQ);
}

void SW_BRAKE_IRQ(){
    SW_BRAKE.rise(NULL);
    SW_BRAKE.fall(NULL);
    wait_us(5000);
    if (SW_BRAKE == 1){
        switchMonitor.flags_set(61);
    }
    if (SW_BRAKE == 0){
        switchMonitor.flags_set(60);
    }
    SW_BRAKE.rise(SW_BRAKE_IRQ);
    SW_BRAKE.fall(SW_BRAKE_IRQ);
}

void SW_REV_IRQ(){
    SW_REV.rise(NULL);
    SW_REV.fall(NULL);
    wait_us(5000);
    if (SW_REV == 1){
        switchMonitor.flags_set(71);
    }
    if (SW_BRAKE == 0){
        switchMonitor.flags_set(70);
    }
    SW_REV.rise(SW_REV_IRQ);
    SW_REV.fall(SW_REV_IRQ);
}

void SW_M_EN_IRQ(){
    SW_M_EN.rise(NULL);
    SW_M_EN.fall(NULL);
    wait_us(5000);
    if (SW_M_EN == 1){
        switchMonitor.flags_set(81);
    }
    if (SW_M_EN == 0){
        switchMonitor.flags_set(80);
    }
    SW_M_EN.rise(SW_M_EN_IRQ);
    SW_M_EN.fall(SW_M_EN_IRQ);
}

void SW_M_DE_IRQ(){
    SW_M_DE.rise(NULL);
    SW_M_DE.fall(NULL);
    wait_us(5000);
    if (SW_M_DE == 1){
        switchMonitor.flags_set(91);
    }
    if (SW_M_DE == 0){
        switchMonitor.flags_set(90);
    }
    SW_M_DE.rise(SW_M_DE_IRQ);
    SW_M_DE.fall(SW_M_DE_IRQ);
}

void switchDetection(){
    SW_1.rise(SW_1_IRQ);
    SW_1.fall(SW_1_IRQ);
    SW_2.rise(SW_2_IRQ);
    SW_2.fall(SW_2_IRQ);
    SW_ASCEND.rise(SW_ASC_IRQ);
    SW_ASCEND.fall(SW_ASC_IRQ);
    SW_DESCEND.rise(SW_DESC_IRQ);
    SW_DESCEND.fall(SW_DESC_IRQ);
    SW_LIGHTS.rise(SW_LIGHTS_IRQ);
    SW_LIGHTS.fall(SW_LIGHTS_IRQ);
    SW_BRAKE.fall(SW_BRAKE_IRQ);
    SW_BRAKE.rise(SW_BRAKE_IRQ);
    SW_REV.rise(SW_REV_IRQ);
    SW_REV.fall(SW_REV_IRQ);
    SW_M_EN.rise(SW_M_EN_IRQ);
    SW_M_EN.fall(SW_M_EN_IRQ);
    SW_M_DE.rise(SW_M_DE_IRQ);
    SW_M_DE.rise(SW_M_DE_IRQ);
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

            case 31:
            printf("Ascend Switch Activated\n");
            SW_ASC_LED = 1;
            break;

            case 30:
            printf("Ascend Switch Deactivated\n");
            SW_ASC_LED = 0;
            break;

            case 41:
            printf("Descend Switch Activated\n");
            SW_DESC_LED = 1;
            break;

            case 40:
            printf("Descend Switch Deactivated\n");
            SW_DESC_LED = 0;
            break;

            case 51:
            printf("Lights Switch Activated\n");
            SW_LIGHTS_LED = 1;
            break;

            case 50:
            printf("Lights Switch Deactivated\n");
            SW_LIGHTS_LED = 0;
            break;

            case 61:
            printf("Brake Switch Activated\n");
            SW_BRAKE_LED = 1;
            break;

            case 60:
            printf("Brake Switch Deactivated\n");
            SW_BRAKE_LED = 0;
            break;

            case 71:
            printf("Reverse Switch Activated\n");
            SW_REV_LED = 1;
            break;

            case 70:
            printf("Reverse Switch Deactivated\n");
            SW_REV_LED = 0;
            break;

            case 81:
            printf("Engage Motors Switch Activated\n");
            SW_M_EN_LED = 1;
            break;

            case 80:
            printf("Engage Motors Switch Deactivated\n");
            SW_M_EN_LED = 0;
            break;

            case 91:
            printf("Disengage Motors Switch Activated\n");
            SW_M_DE_LED = 1;
            break;

            case 90:
            printf("Disengage Motors Switch Deactivated\n");
            SW_M_DE_LED = 0;
            break;
            
        }
    }
}