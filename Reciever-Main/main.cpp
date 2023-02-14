/**
    @file Main.cpp
    Main file for Final Year project Receiver - Luke Waller
**/
#include <mbed.h>
#include "ESC.h"
#include "PinNames.h"

#define SeroPin PE_6

ESC servo(SeroPin);

int main(){
    while(true){
    wait_us(5000000);
    servo.write(1.0f);
    wait_us(5000000);
    servo.write(0.0f);
    }

}

/*
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
#include "Buzzer.h"

#define NRF24L01_RX_ADDRESS ((unsigned long long) 0x7878787878)
#define NRF24L01_TX_ADDRESS ((unsigned long long) 0x7878787878)

#define TRANSFER_SIZE   5
#define DEFAULT_PIPE    0
#define CALIBRATE       1
#define MOTOR_OFF       0.0f
#define MOTOR_ON        1.0f

// Radio transeiver
// MOSI, MISO, SCK, CNS, CE, IRQ - must be an interrupt pin 6 
nRF24L01P nRF24L01(MOSI, MISO, SCK, CSN, CE, IRQ);

// Reat Drive Motors
ESC FWDLeftMotor(FWD_LHS_MOTOR), 
    FWDRightMotor(FWD_RHS_MOTOR),
    REVLeftMotor(REV_LHS_MOTOR),
    REVRightMotor(REV_RHS_MOTOR);

// Conveyor Motors
L298N ConvMotor1(CONV_MOTOR_1_A, CONV_MOTOR_1_B, CONV_MOTOR_1_ENABLE),
      ConvMotor2(CONV_MOTOR_2_A, CONV_MOTOR_2_B, CONV_MOTOR_2_ENABLE);

InterruptIn bat30(Bat_30_PERCENT), bat15(Bat_15_PERCENT),   // battery monitoring
            btn1(BTN_1), btn2(BTN_2),                       // button inputs
            SW1(SW_1), SW2(SW_2), SW3(SW_3), SW4(SW_4), SW5(SW_5), SW6(SW_6),                // switches
            IR1(IR_1), IR2(IR_2), IR3(IR_3), IR4(IR_4);                           // IR inputs

Buzzer buzzer(BUZZER);

DigitalOut led1(LED_1), led2(LED_10), led3(LED_9), led4(LED_8), led5(LED_7), led6(LED_6), led7(LED_5), led8(LED_4), led9(LED_2), led10(LED_3);

float fwdLeftMotorThrottle = 0, fwdRightMotorThrottle = 0;
float revLeftMotorThrottle = 0, revRightMotorThrottle = 0;

Mutex LeftMotorLock, RightMotorLock;

Thread LeftMotorThread, RightMotorThread, RadioThread, LEDThread, IRThread, InputThread, bat30percentThread, bat15percentThread;

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
void flipOutput(DigitalOut pin);

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

    printf("Starting Board...\n");

    buzzer = true;
    led2 = 1;

    wait_us(5000000);

    nRF24L01.powerUp();
    nRF24L01.setTransferSize(TRANSFER_SIZE);
    nRF24L01.setAirDataRate(NRF24L01P_DATARATE_2_MBPS);
    nRF24L01.setRxAddress(NRF24L01_RX_ADDRESS);
    nRF24L01.setTxAddress(NRF24L01_TX_ADDRESS);


// Display the (default) setup of the nRF24L01+ chip
    printf("nRF24L01 Frequency    : %d MHz\n",  nRF24L01.getRfFrequency() );
    printf("nRF24L01 Output Power : %d dBm\n",  nRF24L01.getRfOutputPower() );
    printf("nRF24L01 Data Rate    : %d kbps\n", nRF24L01.getAirDataRate() );
    printf("nRF24L01 Transfer Size: %d bits\n", nRF24L01.getTransferSize(DEFAULT_PIPE));
    printf("nRF24L01 TX Address   : 0x%010llX\n", nRF24L01.getTxAddress() );
    printf("nRF24L01 RX Address   : 0x%010llX\n", nRF24L01.getRxAddress() );

    nRF24L01.setReceiveMode();

    nRF24L01.enable();

    bat30.rise(bat30PercentIRQ);
    bat15.rise(bat15PercentIRQ);
    btn1.rise(btn1IRQ);
    btn2.rise(btn2IRQ);
    SW1.rise(SW1IRQ);
    SW2.rise(SW2IRQ);
    SW3.rise(SW3IRQ);
    SW4.rise(SW4IRQ);
    SW5.rise(SW5IRQ);
    SW6.rise(SW6IRQ);
    IR1.rise(IRIRQ);
    IR2.rise(IRIRQ);
    IR3.rise(IRIRQ);
    IR4.rise(IRIRQ);

    LeftMotorThread.start(LeftMotorThreadMethod);
    RightMotorThread.start(RightMotorThreadMethod);
    RadioThread.start(RadioReceiveMethod);
    LEDThread.start(LEDMethod);
    IRThread.start(IRMethod);
    InputThread.start(InputMethod);
    bat30percentThread.start(bat30percentMethod);
    bat15percentThread.start(bat15percentMethod);

    while (true) {
    LEDThread.flags_set(1);
    ThisThread::sleep_for(1s);
    }

}

void RadioReceiveMethod(){
    PRINT("Radio Thread Started\n");
    while (true) {
        if (nRF24L01.readable()) {
            nRF24L01.read(DEFAULT_PIPE, rxData, TRANSFER_SIZE);
            printf("Received Data: %s\n", rxData);
            switch (rxData[0]){
            case '1': // POT
                switch (rxData[1]){
                case '1': // Left Pitch
                    switch (rxData[2]) {
                    case '0':{ // Forwards
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        revLeftMotorThrottle = MOTOR_OFF;
                        fwdLeftMotorThrottle = ThrottleValue(&rxData[3]) / 10;
                        LeftMotorThread.flags_set(1);
                        LeftMotorLock.unlock();
                        printf("LEFT FWDs : \n");
                        break;
                    }
                break;
                    case '1': // Reverse
                        // set value of throttle
                        LeftMotorLock.trylock_for(10ms);
                        fwdLeftMotorThrottle = MOTOR_OFF;
                        revLeftMotorThrottle = ThrottleValue(&rxData[3]) / 10;
                        LeftMotorThread.flags_set(1);
                        LeftMotorLock.unlock();
                        printf("LEFT REV : %f\n", revLeftMotorThrottle);
                        break;
                    default:
                        break;
                    }
                break;
                case '2': // Left Roll - currently have no function
                    switch (rxData[2]) {
                    case '0': // Forwards
                        break;
                    case '1': // Reverse
                        // set value of throttle                    default:
                        break;
                    default:
                        break;
                    }
                break;
                case '3': // Right Pitch
                    switch (rxData[2]) {
                    case '0':{ // Forwards
                        // set value of throttle
                        RightMotorLock.trylock_for(10ms);
                        revRightMotorThrottle = MOTOR_OFF;
                        fwdRightMotorThrottle = ThrottleValue(&rxData[3]) / 10;
                        RightMotorThread.flags_set(1);
                        RightMotorLock.unlock();
                        printf("LEFT FWDs : \n");
                        break;
                    }
                break;
                    case '1': // Reverse
                        // set value of throttle
                        RightMotorLock.trylock_for(10ms);
                        fwdRightMotorThrottle = MOTOR_OFF;
                        revRightMotorThrottle = ThrottleValue(&rxData[3]) / 10;
                        RightMotorThread.flags_set(1);
                        RightMotorLock.unlock();
                        printf("LEFT REV : %f\n", revLeftMotorThrottle);
                        break;
                    default:
                        break;
                    }
                break;
                case '4': // Right Roll - currently have no function
                    switch (rxData[2]) {
                    case '0': // Forwards
                        break;
                    case '1': // Reverse
                        // set value of throttle                    default:
                        break;
                    }
                default:
                    break;
                }
                break;
            case '2': // BUTTON
                switch (rxData[1]) {
                case '1': // Button 1 - motors forwards
                    printf("Motors Forwards\n");
                    ConvMotor1 = 1, ConvMotor2 = 1;
                    break;
                case '2': // Button 2
                case '3': // Button 3 - motors reverse
                    printf("Motors Reverse\n");
                    ConvMotor1 = -1, ConvMotor2 = -1;
                    break;
                default:
                    break;
                }
                break;
            case '3': // SWITCH
                switch (rxData[3]) {
                case '1': // Switch ON - enable motors
                    printf("Switch ON\n");
                    ConvMotor1 = true, ConvMotor2 = true;
                    break;
                case '0': // Switch OFF - disable motors
                    printf("Switch OFF\n");
                    ConvMotor1 = false, ConvMotor2 = false;
                    break;
                default:
                    break;
                }
                break;
            case 'T': // test send
                break;
            default:
                PRINT("Invalid Input\n");
                break;
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
        ThisThread::flags_wait_any(0x7fffffff, true);
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
        ThisThread::flags_wait_any(0x7fffffff, true);
        RightMotorLock.trylock_for(1ms);
        FWDRightMotor = fwdRightMotorThrottle;
        REVRightMotor = revRightMotorThrottle;
        RightMotorLock.unlock();
    }
}

void LEDMethod(){
    
    printf("LED Thread Running\n");

    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(flag);
        switch (flag) {
        case 1:
            flipOutput(led1);
            break;
        case 2:
            flipOutput(led2);
            break;
        case 3:
            flipOutput(led3);
            break;
        case 4:
            flipOutput(led4);
            break;
        case 5: 
            flipOutput(led5);
            break;
        case 6:
            flipOutput(led6);
            break;
        case 7:
            flipOutput(led7);
            break;
        case 8:
            flipOutput(led8);
            break;
        case 9:
            flipOutput(led9);
            break;
        case 10:
            flipOutput(led10);
            break;
        default:
            break;
        
        }
    }
}

void IRMethod(){

    printf("IR Thread Running\n");

    ThisThread::flags_wait_any(0x7fffffff, true);
    while (true) {
        if (rubbishContainerFull == 0) { 
            rubbishContainerFull = 1;
            printf("Basket Full!!\n");
            buzzer = 1;
            ThisThread::sleep_for(2s);
            buzzer = 0;
            ThisThread::sleep_for(5s);
        } else {
            // disable IRQ Interrupts
            IR1.rise(NULL);
            IR2.rise(NULL);
            IR3.rise(NULL);
            IR4.rise(NULL);
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
        case 1: // button 1 - disable alarms
            printf("Button 1 pressed - Alarms Disabled\n");
            battery15percent = 0, 
            battery30percent = 0;
            bat30.rise(NULL);
            bat15.rise(NULL);
            IR2.rise(NULL);
            IR4.rise(NULL);
            buzzer = false;
            led2 = 0;
            break;
        case 2: // button 2
            printf("Litter Basket Emptied - Sensors Reset, Buzzer Renabled\n");
            buzzer = true;
            led2 = 1;
            rubbishContainerFull = 0;   
            IR2.rise(IRIRQ);
            IR4.rise(IRIRQ);        
            break;
        case 4: // switch 1 - disable the motors - 4 quick beeps
            printf("Switch 1 Off - Motors Disabled\n");
            led3 = 0, led4 = 0;
            for (int i = 3; i < 11; i++){
                buzzer = i % 2;
                ThisThread::sleep_for(100ms);
            }
            break;
        case 8: // switch 2 - enable the motors - 4 long beeps
            printf("Switch 1 On - Motors Enabled\n");
            led3 = 1, led4 = 1;
            for (int i = 3; i < 11; i++){
                buzzer = i % 2;
                ThisThread::sleep_for(500ms);
            }
            break;
        case 16: // switch 3 - not in use
            break;
        case 32: // switch 4 - not in use
            break; 
        case 64: // switch 5 - not in use
            break;
        case 128: // switch 6 - not in use
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
            printf("Buzz\n");
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
            printf("Buzz Buzz\n");
            buzzer = 1;
            ThisThread::sleep_for(1s);
            buzzer = 0;
            int x = rubbishContainerFull == 1 ? 1 : 2;
            ThisThread::sleep_for(2s);
        }        
    }

}

void bat30PercentIRQ(){
    bat30.rise(NULL);
    wait_us(5000);
    if (bat30 == 1){
        bat30percentThread.flags_set(1);
    }
    bat30.rise(bat30PercentIRQ);
}

void bat15PercentIRQ(){
    bat15.rise(NULL);
    wait_us(5000);
    if (bat15 == 1){
        bat15percentThread.flags_set(1);
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
    IRThread.flags_set(1);
    LEDThread.flags_set(1);
    IR1.rise(IRIRQ);
    IR2.rise(IRIRQ);
    IR3.rise(IRIRQ);
    IR4.rise(IRIRQ);
}

void flipOutput(DigitalOut pin){
    pin = !pin; 
}
*/
