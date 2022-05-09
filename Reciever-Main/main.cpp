/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
**/

#include <cstdio>
#include <mbed.h>
#include <nRF24L01P.h>
#include "DigitalIn.h"
#include "HARDWARE.h"
#include "ESC.h"
#include "InterruptIn.h"
#include "PinNames.h"
#include "ThisThread.h"
#include <PwmOut.h>
#include "L298N.h"

#define TRANSFER_SIZE   5
#define DEFAULT_PIPE    0
#define CALIBRATE       0
#define MOTOR_OFF       0.0f
#define MOTOR_ON        1.0f

// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

ESC FWDLeftMotor(FWD_LHS_MOTOR), 
    FWDRightMotor(FWD_RHS_MOTOR),
    REVLeftMotor(REV_LHS_MOTOR),
    REVRightMotor(REV_RHS_MOTOR);

L298N ConvMotor1(CONV_MOTOR_1_A, CONV_MOTOR_1_B, CONV_MOTOR_1_ENABLE),
      ConvMotor2(CONV_MOTOR_2_A, CONV_MOTOR_2_B, CONV_MOTOR_2_ENABLE);

InterruptIn bat30(Bat_30_PERCENT), bat15(Bat_15_PERCENT), // battery monitoring
            btn1(BTN_1), btn2(BTN_2), // button inputs
            SW1(SW_1), SW2(SW_2), SW3(SW_3), SW4(SW_4), SW5(SW_5),SW6(SW_6), // switch inputs
            IR1(IR_1), IR2(IR_2), IR3(IR_3), IR4(IR_4); // IR Sensor inputs

PwmOut buzzer(BUZZER);

BusOut LEDs(LED_1, LED_10, LED_9, LED_8, LED_7, LED_6, LED_5, LED_4, LED_2, LED_3);

float fwdLeftMotorThrottle = 0, fwdRightMotorThrottle = 0;
float revLeftMotorThrottle = 0, revRightMotorThrottle = 0;

Mutex LeftMotorLock, RightMotorLock;

Thread LeftMotorThread, RightMotorThread, RadioThread, lowBatteryThread, LEDThread, IRThread, InputThread, bat30percentThread, bat15percentThread;

char rxData[TRANSFER_SIZE];
float POTVal = 0;
int rxDataCnt = 0;

int rubbishContainerFull = 0;
int battery30percent = 0;
int battery15percent = 0;

void LeftMotorThreadMethod();
void RightMotorThreadMethod();
void RadioReceiveMethod();
void lowBatteryMethod();
void LEDMethod();
void IRMethod();
void InputMethod();
void bat30percentMethod();
void bat15percentMethod();
float ThrottleValue(char* data);

// IRQ Methods 
void bat30PercentIRQ();
void bat15PercentIRQ();
void btn1IRQ();
void btn2IRQ();
void SW1IRQ();
void SW2IRQ();
void SW3IRQ();
void SW4IRQ();
void SW5IRQ();
void SW6IRQ();
void IRIRQ();

int main() {

    // enabling the two conveyer motos
    ConvMotor1 = true, ConvMotor2 = true;

    printf("Starting Board...\n");

        // wait_us(5000000);

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
    RightMotorThread.start(RightMotorThreadMethod);
    RadioThread.start(RadioReceiveMethod);
    lowBatteryThread.start(lowBatteryMethod);
    LEDThread.start(LEDMethod);
    IRThread.start(IRMethod);
    InputThread.start(InputMethod);
    bat30percentThread.start(bat30percentMethod);
    bat15percentThread.start(bat15percentMethod);

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
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        revLeftMotorThrottle = MOTOR_OFF;
                        fwdLeftMotorThrottle = ThrottleValue(&rxData[3]);
                        LeftMotorLock.unlock();
                        break;
                    }
                    case '1': // Reverse
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        fwdLeftMotorThrottle = MOTOR_OFF;
                        revLeftMotorThrottle = ThrottleValue(&rxData[3]);
                        LeftMotorLock.unlock();
                    default:
                        break;
                    }
                case '2': // Left Roll - currently hove no function
                    switch (rxData[2]) {
                    case '0': // Forward
                    case '1': // Reverse
                    default:
                        break;
                    }
                case '3': // Right Pitch
                    switch (rxData[2]) {
                    case '0': // Forwards
                        // set value of throttle
                        RightMotorLock.trylock_for(10ms);
                        revRightMotorThrottle = MOTOR_OFF;
                        fwdRightMotorThrottle = ThrottleValue(&rxData[3]);
                        RightMotorLock.unlock();
                    case '1': // Reverse
                        // set value of throttle
                        RightMotorLock.trylock_for(10ms);
                        fwdRightMotorThrottle = MOTOR_OFF;
                        revRightMotorThrottle = ThrottleValue(&rxData[3]);
                        RightMotorLock.unlock();
                    default:
                        break;
                    }
                case '4': // Right Roll - currently have no function
                    switch (rxData[2]) {
                    case '0': // Forwards
                    case '1': // Reverse
                        // set value of throttle                    default:
                        break;
                    }
                default:
                    break;
                }
            case '2': // BUTTON
                switch (rxData[1]) {
                case '1': // Button 1 - motors forwards
                    ConvMotor1 = 1, ConvMotor1 = 1;
                case '2': // Button 2
                case '3': // Button 3 - motors reverse
                    ConvMotor1 = -1, ConvMotor2 = -1;
                default:
                    break;
                }
                break;
            case '3': // SWITCH
                switch (rxData[2]) {
                case '1': // Switch ON - enable motors
                    ConvMotor1 = true, ConvMotor2 = true;
                case '2': // Switch OFF - disable motors
                    ConvMotor1 = false, ConvMotor2 = false;
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
    fwdLeftMotorThrottle = 0;
    revLeftMotorThrottle = 0;
    LeftMotorLock.unlock();

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff);
        LeftMotorLock.trylock_for(1ms);
        FWDLeftMotor = fwdLeftMotorThrottle;
        REVLeftMotor = revLeftMotorThrottle;
        LeftMotorLock.unlock();
    }
}

void RightMotorThreadMethod(){

    printf("Right Motor Thread Started\n");

    RightMotorLock.trylock_for(10ms);
    fwdRightMotorThrottle = 0;
    revRightMotorThrottle = 0;
    RightMotorLock.unlock();

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff);
        RightMotorLock.trylock_for(1ms);
        FWDRightMotor = fwdRightMotorThrottle;
        REVRightMotor = revRightMotorThrottle;
        RightMotorLock.unlock();
    }
}

void lowBatteryMethod(){

    printf("Low Battery Thread Running\n");

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(flag);
        printf("Flag = %d\n", flag);
        switch (flag) {
        case 1: // battery at 30%
            printf("Battery at 30%%\n");
            break;
        case 2: // battery at 15%
            printf("Battery at 15%%\n");
            break;
        case 3: // deactivate thread
            break;
        default:
            printf("Error!\n");
            break;
        }
    }
}

void LEDMethod(){
    
    printf("LED Thread Running\n");

    while (true) {
    }
}

void IRMethod(){

    printf("IR Thread Running");

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, true);
        if (rubbishContainerFull == 0) {
            rubbishContainerFull = 1;
            // buzz and LEDs
        } else {
            // do nothing?
        }
    }
}

void InputMethod(){

    printf("Input Thread Started\n");

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);
        printf("Flag = %d\n", flag);
        switch (flag) {
        case 1: // button 1
            break;
        case 2: // button 2
            break;
        case 4: // switch 1
            break;
        case 8: // switch 2
            break;
        case 16: // switch 3
            break;
        case 32: // switch 4
            break;
        case 64: // switch 5
            break;
        case 128: // switch 6
            break;
        default:
            break;
        }
    }

}

void bat30percentMethod(){

    printf("Battery 30%% Thread Started\n");

    ThisThread::flags_wait_any(0x7fffffff, false);
    while (true) {
        if ((battery30percent == 1) && (battery15percent == 1)) {
            return;
        } else {
            buzzer = 1;
            ThisThread::sleep_for(1s);
            buzzer = 0;
            ThisThread::sleep_for(10s);
        }
    }
}

void bat15percentMethod(){
    
    printf("Battery 15%% Thread Started\n");

    ThisThread::flags_wait_any(0x7fffffff, false);
    while (true) {
        if ((battery30percent == 1) && (battery15percent == 1)){
            buzzer = 1;
            ThisThread::sleep_for(1s);
            buzzer = 0;
            ThisThread::sleep_for(1s);
        }        
    }

}

void bat30PercentIRQ(){
    bat30.rise(NULL);
    wait_us(5000);
    if (bat30 == 1){
        lowBatteryThread.flags_set(1);
    }
    bat30.rise(bat30PercentIRQ);
}

void bat15PercentIRQ(){
    bat15.rise(NULL);
    wait_us(5000);
    if (bat15 == 1){
        lowBatteryThread.flags_set(2);
    }
}

void btn1IRQ(){
    btn1.rise(NULL);
    wait_us(5000);
    if (btn1 == 1){
        InputThread.flags_set(1);
    }
    btn1.rise(btn1IRQ);
}

void btn2IRQ(){
    btn2.rise(NULL);
    wait_us(5000);
    if (btn2 == 1){
        InputThread.flags_set(2);
    }
    btn2.rise(btn2IRQ);
}

void SW1IRQ(){
    SW1.rise(NULL);
    wait_us(5000);
    if (SW1 == 1){
        InputThread.flags_set(4);
    }
    SW1.rise(SW1IRQ);
}

void SW2IRQ(){
    SW2.rise(NULL);
    wait_us(5000);
    if (SW2 == 1){
        InputThread.flags_set(8);
    }
    SW2.rise(SW2IRQ);
}

void SW3IRQ(){
    SW3.rise(NULL);
    wait_us(5000);
    if (SW3 == 1){
        InputThread.flags_set(16);
    }
    SW3.rise(SW3IRQ);
}

void SW4IRQ(){
    SW4.rise(NULL);
    wait_us(5000);
    if (btn1 == 1){
        InputThread.flags_set(32);
    }
    SW4.rise(SW4IRQ);
}

void SW5IRQ(){
    SW5.rise(NULL);
    wait_us(5000);
    if (SW5 == 1){
        InputThread.flags_set(64);
    }
    SW5.rise(SW5IRQ);
}

void SW6IRQ(){
    SW6.rise(NULL);
    wait_us(5000);
    if (SW6 == 1){
        InputThread.flags_set(128);
    }
    SW6.rise(SW6IRQ);
}

void IRIRQ(){
    IR1.rise(NULL);
    IR2.rise(NULL);
    IR3.rise(NULL);
    IR4.rise(NULL);
    wait_us(5000);
    if (btn1 == 1){
        IRThread.flags_set(1);
    }
    IR1.rise(IRIRQ);
    IR2.rise(IRIRQ);
    IR3.rise(IRIRQ);
    IR4.rise(IRIRQ);
}

