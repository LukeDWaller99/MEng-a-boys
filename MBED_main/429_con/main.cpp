#include "DigitalIn.h"
#include "DigitalOut.h"
#include "F429ZI_Hardware.h"
#include "InterruptIn.h"
#include <Callback.h>
#include <ThisThread.h>
#include <mbed.h>
#include <rtos.h>

// Joysticks
AnalogIn L_Pitch(L_PITCH);
AnalogIn L_Roll(L_ROLL);
AnalogIn R_Pitch(R_PITCH);
AnalogIn R_Roll(R_ROLL);

Mutex PotLock;
Thread switchMonitor, PotThread;
Ticker joystickTicker;

int output = 0;

const int leftPitchPosMask = 0b00000111;
const int leftPitchNegMask = 0b00000111;
const int leftPitchZeroMask = 0b00000000;

const int leftRollPosMask = 0b00010111;
const int leftRollNegMask = 0b00011111;
const int leftRollZeroMask = 0b00010000;

const int rightPitchPosMask = 0b00100111;
const int rightPitchNegMask = 0b00101111;
const int rightPitchZeroMask = 0b01000000;

const int rightRollPosMask = 0b00110111;
const int rightRollNegMask = 0b00111111;
const int rightRollZeroMask = 0b00110000;

float potVals[6], oldPotVals[6];

struct stickData {
  char fwdLeftPitch[TRANSFER_SIZE] = {LEFT_PITCH_FWD},
       fwdLeftRoll[TRANSFER_SIZE] = {LEFT_ROLL_FWD},
       fwdRightPitch[TRANSFER_SIZE] = {RIGHT_PITCH_FWD},
       fwdRightRoll[TRANSFER_SIZE] = {RIGHT_ROLL_FWD},
       fwdLeftPitchTemp[TRANSFER_SIZE], fwdLeftRollTemp[TRANSFER_SIZE],
       fwdRightPitchTemp[TRANSFER_SIZE], fwdRightRollTemp[TRANSFER_SIZE],
       revLeftPitch[TRANSFER_SIZE] = {LEFT_PITCH_REV},
       revLeftRoll[TRANSFER_SIZE] = {LEFT_ROLL_REV},
       revRightPitch[TRANSFER_SIZE] = {RIGHT_PITCH_REV},
       revRightRoll[TRANSFER_SIZE] = {RIGHT_PITCH_REV},
       revLeftPitchTemp[TRANSFER_SIZE], revLeftRollTemp[TRANSFER_SIZE],
       revRightPitchTemp[TRANSFER_SIZE], revRightRollTemp[TRANSFER_SIZE];
};

// Onboard Peripherals
// InterruptIn USER_BTN(USR_BTN);
DigitalOut USER_GREEN(USER_LED_GREEN);
DigitalOut USER_RED(USER_LED_RED);
DigitalOut USER_BLUE(USER_LED_BLUE);

// InterruptIn SW_1(SWITCH_1);
// InterruptIn SW_2(SWITCH_2);
// //InterruptIn SW_BUZZ(BUZZER);
// InterruptIn SW_ASCEND(ASCEND);
// InterruptIn SW_DESCEND(DESCEND);
// InterruptIn SW_LIGHTS(LIGHTS);
// InterruptIn SW_BRAKE(BRAKE_MODE);
// InterruptIn SW_REV(REV_MODE);
// //InterruptIn SW_M_MODE_1(MOTOR_MODE_1);
// //InterruptIn SW_M_MODE_2(MOTOR_MODE_2);
// InterruptIn SW_M_EN(MOTOR_EN);
// InterruptIn SW_M_DE(MOTOR_DE);
// //InterruptIn SW_KILL(KILL_SWITCH);

// DigitalOut SW_1_LED(SWITCH_1_LED);
// DigitalOut SW_2_LED(SWITCH_2_LED);
// DigitalOut SW_ASC_LED(ASCEND_LED);
// DigitalOut SW_DESC_LED(DESCEND_LED);
// DigitalOut M_MODE_1_LED(MOTOR_MODE_1_LED);
// DigitalOut M_MODE_2_LED(MOTOR_MODE_2_LED);
// DigitalOut SW_BRAKE_LED(BRAKE_LED);
// DigitalOut SW_REV_LED(REV_LED);
// DigitalOut SW_KILL_LED(KILL_LED);
// DigitalOut SW_LIGHTS_LED(LIGHTS_LED);
// DigitalOut SW_M_EN_LED(EN_LED);
// DigitalOut SW_M_DE_LED(DE_LED);

// COLLISION LEDS
DigitalOut C_LED_1(COL_SENSE_1);
DigitalOut C_LED_2(COL_SENSE_2);
DigitalOut C_LED_3(COL_SENSE_3);
DigitalOut C_LED_4(COL_SENSE_4);
DigitalOut C_LED_5(COL_SENSE_5);
DigitalOut C_LED_6(COL_SENSE_6);
DigitalOut C_LED_7(COL_SENSE_7);
DigitalOut C_LED_8(COL_SENSE_8);

void joystickIRQ();
void PotMethod();
void switchMonitorMethod();
void switchDetection();
void SW_1_IRQ();
void SW_2_IRQ();
void SW_ASC_IRQ();
void SW_DESC_IRQ();
void SW_MODE_1_IRQ();
void SW_MODE_2_IRQ();
void SW_LIGHTS_IRQ();
void SW_BRAKE_IRQ();
void SW_REV_IRQ();
void SW_M_EN_IRQ();
void SW_M_DE_IRQ();
// void SW_KILL_IRQ();

void collisionLEDs() {
  C_LED_1 = 1;
  wait_us(50000);
  C_LED_1 = 0;
  C_LED_2 = 1;
  wait_us(50000);
  C_LED_2 = 0;
  C_LED_3 = 1;
  wait_us(50000);
  C_LED_3 = 0;
  C_LED_4 = 1;
  wait_us(50000);
  C_LED_4 = 0;
  C_LED_5 = 1;
  wait_us(50000);
  C_LED_5 = 0;
  C_LED_6 = 1;
  wait_us(50000);
  C_LED_6 = 0;
  C_LED_7 = 1;
  wait_us(50000);
  C_LED_7 = 0;
  C_LED_8 = 1;
  wait_us(50000);
  C_LED_8 = 0;
}

SPI myspi(PB_5, PB_4, PB_3); // mosi, miso, sclk
// same as the pins defined on PCB
DigitalOut CS(PA_4);

int main() {
  PotThread.start(PotMethod);
  printf("Starting F429 Controller Board\n");
  USER_BLUE = 1;
  wait_us(10000);
  USER_BLUE = 0;
  // wait and see!!!!!
  //joystickTicker.attach(joystickIRQ, 200ms);

  // switchDetection();
  // switchMonitor.start(switchMonitorMethod);
  CS = 1;
  myspi.frequency(1000000);
  myspi.format(8, 0);

  printf("\nSPI 8-bit test launched\n");
//   CS = 0;
//   myspi.write(0b00000000);
//   CS = 1;
    int data = 0;
  float rawLPitch;
//   while (1) {
//             rawLPitch = L_Pitch.read(); 
//             printf("L_P: %d\n", rawLPitch);
//             CS = 0;
//             myspi.write(rawLPitch);
//             CS = 1;
//             wait_us(1000000);
//   }

while(1){
      printf("data: %d\n", data);
      CS = 0;
      myspi.write(data);
      CS = 1;
      data++;
      wait_us(1000000);
   }
  //     //CS = 0;
  // myspi.write(0b00000000);
  //     //CS = 1;
  // wait_us(100000);
  //     collisionLEDs();
  // //     //cs = 0;
  // //     data_read = myspi.write(data_write);
  // //     //cs = 1;
  // //     printf("sent 0x%2x, read: 0x%2x   ", data_write, data_read);

  // //     if ((uint8_t)(data_read + 1) == (uint8_t)data_write) {
  // //         printf("OK\n");
  // //     } else {
  // //         printf("*FAIL*\n");
  // //     }

  // // wait_us(100000000);
  // // data_write++;
  //}
}

// JOYSTICK CONTROLS

void joystickIRQ() {
  PotThread.flags_set(1);
  // USER_GREEN = 1;
  // wait_us(10000);
  // USER_GREEN = 0;
}

// void SW_1_IRQ(){
//     SW_1.rise(NULL);
//     SW_1.fall(NULL);
//     wait_us(5000);
//     if (SW_1 == 1) {
//         switchMonitor.flags_set(11);
//     }
//     if (SW_1 == 0){
//         switchMonitor.flags_set(10);
//     }
//     SW_1.rise(SW_1_IRQ);
//     SW_1.fall(SW_1_IRQ);
// }

// void SW_2_IRQ(){
//     SW_2.rise(NULL);
//     SW_2.fall(NULL);
//     wait_us(5000);
//     if (SW_2 == 1) {
//         switchMonitor.flags_set(21);
//     }
//     if (SW_2 == 0) {
//         switchMonitor.flags_set(20);
//     }
//     SW_2.rise(SW_2_IRQ);
//     SW_2.fall(SW_2_IRQ);
// }

// void SW_ASC_IRQ(){
//     SW_ASCEND.rise(NULL);
//     SW_ASCEND.fall(NULL);
//     wait_us(5000);
//     if (SW_2 == 1){
//         switchMonitor.flags_set(31);
//     }
//     if (SW_2 == 0){
//         switchMonitor.flags_set(30);
//     }
//     SW_ASCEND.rise(SW_ASC_IRQ);
//     SW_ASCEND.fall(SW_ASC_IRQ);
// }

// void SW_DESC_IRQ(){
//     SW_DESCEND.rise(NULL);
//     SW_DESCEND.fall(NULL);
//     wait_us(5000);
//     if (SW_2 == 1){
//         switchMonitor.flags_set(41);
//     }
//     if (SW_2 == 0){
//         switchMonitor.flags_set(40);
//     }
//     SW_DESCEND.rise(SW_DESC_IRQ);
//     SW_DESCEND.fall(SW_DESC_IRQ);
// }

// void SW_LIGHTS_IRQ(){
//     SW_LIGHTS.rise(NULL);
//     SW_LIGHTS.fall(NULL);
//     wait_us(5000);
//     if (SW_LIGHTS == 1){
//         switchMonitor.flags_set(51);
//     }
//     if (SW_LIGHTS == 0){
//         switchMonitor.flags_set(50);
//     }
//     SW_LIGHTS.rise(SW_LIGHTS_IRQ);
//     SW_LIGHTS.fall(SW_LIGHTS_IRQ);
// }

// void SW_BRAKE_IRQ(){
//     SW_BRAKE.rise(NULL);
//     SW_BRAKE.fall(NULL);
//     wait_us(5000);
//     if (SW_BRAKE == 1){
//         switchMonitor.flags_set(61);
//     }
//     if (SW_BRAKE == 0){
//         switchMonitor.flags_set(60);
//     }
//     SW_BRAKE.rise(SW_BRAKE_IRQ);
//     SW_BRAKE.fall(SW_BRAKE_IRQ);
// }

// void SW_REV_IRQ(){
//     SW_REV.rise(NULL);
//     SW_REV.fall(NULL);
//     wait_us(5000);
//     if (SW_REV == 1){
//         switchMonitor.flags_set(71);
//     }
//     if (SW_BRAKE == 0){
//         switchMonitor.flags_set(70);
//     }
//     SW_REV.rise(SW_REV_IRQ);
//     SW_REV.fall(SW_REV_IRQ);
// }

// void SW_M_EN_IRQ(){
//     SW_M_EN.rise(NULL);
//     SW_M_EN.fall(NULL);
//     wait_us(5000);
//     if (SW_M_EN == 1){
//         switchMonitor.flags_set(81);
//     }
//     if (SW_M_EN == 0){
//         switchMonitor.flags_set(80);
//     }
//     SW_M_EN.rise(SW_M_EN_IRQ);
//     SW_M_EN.fall(SW_M_EN_IRQ);
// }

// void SW_M_DE_IRQ(){
//     SW_M_DE.rise(NULL);
//     SW_M_DE.fall(NULL);
//     wait_us(5000);
//     if (SW_M_DE == 1){
//         switchMonitor.flags_set(91);
//     }
//     if (SW_M_DE == 0){
//         switchMonitor.flags_set(90);
//     }
//     SW_M_DE.rise(SW_M_DE_IRQ);
//     SW_M_DE.fall(SW_M_DE_IRQ);
// }

// // void SW_KILL_IRQ(){
// //     SW_KILL.rise(NULL);
// //     SW_KILL.fall(NULL);
// //     wait_us(5000);
// //     if (SW_KILL == 1){
// //         switchMonitor.flags_set(01);
// //     }
// //     if (SW_KILL == 0){
// //         switchMonitor.flags_set(00);
// //     }
// //     SW_KILL.rise(SW_KILL_IRQ);
// //     SW_KILL.fall(SW_KILL_IRQ);
// // }

void switchDetection() {
  //     SW_1.rise(SW_1_IRQ);
  //     SW_1.fall(SW_1_IRQ);
  //     SW_2.rise(SW_2_IRQ);
  //     SW_2.fall(SW_2_IRQ);
  //     SW_ASCEND.rise(SW_ASC_IRQ);
  //     SW_ASCEND.fall(SW_ASC_IRQ);
  //     SW_DESCEND.rise(SW_DESC_IRQ);
  //     SW_DESCEND.fall(SW_DESC_IRQ);
  //     SW_LIGHTS.rise(SW_LIGHTS_IRQ);
  //     SW_LIGHTS.fall(SW_LIGHTS_IRQ);
  //     SW_BRAKE.rise(SW_BRAKE_IRQ);
  //     SW_BRAKE.fall(SW_BRAKE_IRQ);
  //     SW_REV.rise(SW_REV_IRQ);
  //     SW_REV.fall(SW_REV_IRQ);
  //     SW_M_EN.rise(SW_M_EN_IRQ);
  //     SW_M_EN.fall(SW_M_EN_IRQ);
  //     SW_M_DE.rise(SW_M_DE_IRQ);
  //     SW_M_DE.fall(SW_M_DE_IRQ);
  //     //SW_KILL.rise(SW_KILL_IRQ);
  //    //SW_KILL.fall(SW_KILL_IRQ);
}

// void switchMonitorMethod(){
//     printf("Switch Monitoring Thread Started...\n");
//     while (true) {
//         ThisThread::flags_wait_any(0x7fffffff, false);
//         int flag = ThisThread::flags_get();
//         ThisThread::flags_clear(0x7fffffff);

//         switch (flag) {

//             case 00:
//             printf("Kill Switch Deactivated\n");
//             SW_KILL_LED = 0;
//             // myspi.lock(); //try lock?

//             // myspi.unlock();
//             break;

//             case 01:
//             printf("Kill Switch Activated\n");
//             SW_KILL_LED = 1;
//             break;

//             case 10:
//             printf("SW 1 Deactivated\n");
//             SW_1_LED = 0;
//             break;

//             case 11:
//             printf("SW 1 Activated\n");
//             SW_1_LED = 1;
//             break;

//             case 20:
//             printf("SW 2 Deactivated\n");
//             SW_2_LED = 1;
//             break;

//             case 21:
//             printf("SW 2 Activated\n");
//             SW_2_LED = 1;
//             break;

//             case 30:
//             printf("Ascend Switch Deactivated\n");
//             SW_ASC_LED = 0;
//             break;

//             case 31:
//             printf("Ascend Switch Activated\n");
//             SW_ASC_LED = 1;
//             break;

//             case 40:
//             printf("Descend Switch Deactivated\n");
//             SW_DESC_LED = 0;
//             break;

//             case 41:
//             printf("Descend Switch Activated\n");
//             SW_DESC_LED = 1;
//             break;

//             case 50:
//             printf("Lights Switch Activated\n");
//             SW_LIGHTS_LED = 0;
//             break;

//             case 51:
//             printf("Lights Switch Deactivated\n");
//             SW_LIGHTS_LED = 1;
//             break;

//             case 60:
//             printf("Brake Switch Activated\n");
//             SW_BRAKE_LED = 0;
//             break;

//             case 61:
//             printf("Brake Switch Deactivated\n");
//             SW_BRAKE_LED = 1;
//             break;

//             case 70:
//             printf("Reverse Switch Activated\n");
//             SW_REV_LED = 0;
//             break;

//             case 71:
//             printf("Reverse Switch Activated\n");
//             SW_REV_LED = 1;
//             break;

//             case 80:
//             printf("Engage Motors Switch Deactivated\n");
//             SW_M_EN_LED = 0;
//             break;

//             case 81:
//             printf("Engage Motors Switch Activated\n");
//             SW_M_EN_LED = 1;
//             break;

//             case 90:
//             printf("Disengage Motors Switch Deactivated\n");
//             SW_M_DE_LED = 0;
//             break;

//             case 91:
//             printf("Disengage Motors Switch Activated\n");
//             SW_M_DE_LED = 1;
//             break;

//         }
//     }
// }

void PotMethod() {

  printf("Pot Thread Started\n");

  stickData tx;

  int oldLeftPitchVal = 0;
  int newLeftPitchVal = 0;

  int oldLeftRollVal = 0;
  int newLeftRollVal = 0;

  int oldRightPitchVal = 0;
  int newRightPitchVal = 0;

  int oldRightRollVal = 0;
  int newRightRollVal = 0;

  char tempThrottleChar[2];

  while (true) {

    ThisThread::flags_wait_any(0x7fffffff, true);

    PotLock.trylock_for(10ms);
    //printf("LPitch In : %f\n", L_Pitch.read());
    potVals[0] = ((L_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET) * 7;
    potVals[1] = ((L_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET) * 7;
    potVals[2] = ((R_Pitch.read() * MULTIPLYING_FACTOR) - POT_OFFSET) * 7;
    potVals[3] = ((R_Roll.read() * MULTIPLYING_FACTOR) - POT_OFFSET) * 7;

    newLeftPitchVal = round(potVals[0]);
    newLeftRollVal = round(potVals[1]);
    newRightPitchVal = round(potVals[2]);
    newRightRollVal = round(potVals[3]);

    // for left pitch values
    if (oldLeftPitchVal != newLeftPitchVal) {
      if ((newLeftPitchVal > 0) && (newLeftPitchVal < 8)) { // forwards
        newLeftPitchVal = abs(newLeftPitchVal);
        //printf("+ Left Pitch Val %d\n", newLeftPitchVal);
          // postive +7, negative -7
          output = leftPitchPosMask & newLeftPitchVal;
        //   printf("Left Pos: %d\n", output);
          // pos 0000 0111,
          printf("+ Output : %d\n", output);
          CS = 0;
          myspi.write(output);
          CS = 1;
          //printf("+ Left Pitch: %d\n", output);

      } else if ((newLeftPitchVal < 0) && (newLeftPitchVal > -8)) { // reverse
        newLeftPitchVal = abs(newLeftPitchVal);
        //printf("- Left Pitch Val %d\n", newLeftPitchVal);

          // neg 0000 1111
          output = leftPitchNegMask & (newLeftPitchVal + 8);
          printf("- Output : %d\n", output);
          CS = 0;
          myspi.write(output);
          CS = 1;

          //printf("- Left Pitch: %d\n", output);

      } else { // equal to zero
        newLeftPitchVal = 0;
        //printf(" 0 Left Pitch Val %d\n", newLeftPitchVal);

        // zero 0000 0000
        output = leftPitchZeroMask & newLeftPitchVal;
        CS = 0;
        myspi.write(output);
        CS = 1;

        printf(" 0 Left Pitch: %d\n", output);
      }
    
/*
    // for left roll values
    if (oldLeftRollVal != newLeftRollVal) {
      if (newLeftRollVal > ROLL_UPPER_LIMIT) { // forwards
        newLeftRollVal = abs(newLeftRollVal);
        sprintf(tempThrottleChar, "%d", newLeftRollVal);
        tx.fwdLeftRoll[3] = tempThrottleChar[0];

        if (newLeftRollVal >= 2) {
          // pos 0001 0111
          output = leftRollPosMask & newLeftRollVal;
          myspi.write(output);
        }

        printf("Left Roll: %x\n", output);
      } else if (newLeftRollVal < ROLL_LOWER_LIMIT) { // reverse
        newLeftRollVal = abs(newLeftRollVal);
        sprintf(tempThrottleChar, "%d", newLeftRollVal);
        tx.revLeftRoll[3] = tempThrottleChar[0];

        if (newLeftRollVal >= 8) {
          // neg 0001 1111
          output = leftRollNegMask & newLeftRollVal;
          myspi.write(output);
        }

        printf("Left Roll: %x\n", output);
      } else { // equal to zero
        newLeftPitchVal = 0;
        sprintf(tempThrottleChar, "%d", newLeftRollVal);
        tx.fwdLeftRoll[3] = tempThrottleChar[0];

        // zero 0001 0000
        output = leftRollZeroMask & newLeftRollVal;
        myspi.write(output);

        printf("Left Roll: %x\n", output);
      }
    }

    //   // for right pitch values
    //   if (oldRightPitchVal != newRightPitchVal) {
    //     if (newRightPitchVal > PITCH_UPPER_LIMIT) { // forwards
    //       newRightPitchVal = abs(newRightPitchVal);
    //       sprintf(tempThrottleChar, "%d", newRightPitchVal);
    //       tx.fwdRightPitch[3] = tempThrottleChar[0];

    //       // pos 0010 0111
    //       output = rightPitchPosMask & newRightPitchVal;
    //       myspi.write(output);

    //       printf("Right Pitch: %x\n", output);
    //     } else if (newRightPitchVal < PITCH_LOWER_LIMIT) { // reverse
    //       newRightPitchVal = abs(newRightPitchVal);
    //       sprintf(tempThrottleChar, "%d", newRightPitchVal);
    //       tx.revRightPitch[3] = tempThrottleChar[0];

    //       // neg 0010 1111
    //       output = rightPitchNegMask & newRightPitchVal;
    //       myspi.write(output);

    //       printf("Right Pitch: %x\n", output);
    //     } else { // equal to zero
    //       newRightPitchVal = 0;
    //       sprintf(tempThrottleChar, "%d", newRightPitchVal);
    //       tx.fwdRightPitch[3] = tempThrottleChar[0];

    //       // zero 0010 0000
    //       output = rightPitchZeroMask & newRightPitchVal;
    //       myspi.write(output);

    //       printf("Right Pitch: %x\n", output);
    //     }
    //   }

    //   // for right roll values
    //   if (oldRightRollVal != newRightRollVal) {
    //     if (newRightRollVal > ROLL_UPPER_LIMIT) { // forwards
    //       newRightRollVal = abs(newRightRollVal);
    //       sprintf(tempThrottleChar, "%d", newRightRollVal);
    //       tx.fwdRightRoll[3] = tempThrottleChar[0];

    //       // pos 0011 0111
    //       output = rightRollPosMask & newRightRollVal;
    //       myspi.write(output);

    //       printf("Right Roll: %x\n", output);
    //     } else if (newRightRollVal < ROLL_LOWER_LIMIT) { // reverse
    //       newRightRollVal = abs(newLeftRollVal);
    //       sprintf(tempThrottleChar, "%d", newRightRollVal);
    //       tx.revRightRoll[3] = tempThrottleChar[0];

    //       // neg 0011 1111
    //       output = rightRollNegMask & newRightRollVal;
    //       myspi.write(output);

    //       printf("Right Roll: %x\n", output);
    //     } else { // equal to zero
    //       newRightPitchVal = 0;
    //       sprintf(tempThrottleChar, "%d", newRightRollVal);
    //       tx.fwdRightRoll[3] = tempThrottleChar[0];

    //       // zero 0011 0000
    //       output = rightRollNegMask & newRightRollVal;
    //       myspi.write(output);

    //       printf("Right Roll: %x\n", output);
    //     }
    //   }*/

    oldLeftPitchVal = newLeftPitchVal;
    // oldLeftRollVal = newLeftRollVal;
    // oldRightPitchVal = newRightPitchVal;
    // oldRightRollVal = newRightRollVal;

    PotLock.unlock();
  }
}
}