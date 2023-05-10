#include "mbed.h"
#include "LCD.h"
#include "L432KC_Hardware.h"
#include "ThisThread.h"
#include "InterruptIn.h"

#define BLINKING_RATE     500ms

InterruptIn UP(D_UP);
//InterruptIn DOWN(D_DOWN);
InterruptIn LEFT(D_LEFT);
// InterruptIn RIGHT(D_RIGHT);
// InterruptIn SEL(D_SEL);
// InterruptIn BACK(D_BACK);
Thread dpadMonitor;
void dpadMonitorMethod();
void dpadDetection();
void up_IRQ();
void down_IRQ();
void left_IRQ();
void right_IRQ();
void sel_IRQ();
void back_IRQ();

char foo [16]= "noah smells";

SPISlave myspi(PB_5, PB_4, PB_3, PA_4); // mosi, miso, sclk, nSS
LCD LCD(LCD_RS, LCD_RW, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
int main() {
    printf("L432 Controller Board Started\n");
    
    myspi.frequency(1000000);
    myspi.format(8, 0);
    myspi.reply(0x5A);
    

    while(1) {
         if (myspi.receive()) {
             int data = myspi.read();
             printf("Received %x2\n",data);
             myspi.reply(data); // Read byte from master and transmit it at the next transaction
         } 
    }
}

void up_IRQ(){
    UP.rise(NULL);
    wait_us(500);
    if (UP == 1){
        dpadMonitor.flags_set(1);
    }
    UP.rise(up_IRQ);
}

void down_IRQ(){
    // DOWN.rise(NULL);
    // wait_us(500);
    // if (DOWN == 1){
    //     dpadMonitor.flags_set(2);
    // }
    // DOWN.rise(down_IRQ);
}

void left_IRQ(){
    LEFT.rise(NULL);
    wait_us(500);
    if (LEFT == 1){
        dpadMonitor.flags_set(3);
    }
    LEFT.rise(left_IRQ);
}

void right_IRQ(){
    // RIGHT.rise(NULL);
    // wait_us(500);
    // if (RIGHT == 1){
    //     dpadMonitor.flags_set(4);
    // }
    // RIGHT.rise(right_IRQ);
}

void sel_IRQ(){
    // SEL.rise(NULL);
    // wait_us(500);
    // if (SEL == 1){
    //     dpadMonitor.flags_set(5);
    // }
    // SEL.rise(sel_IRQ);
}

void back_IRQ(){
    // BACK.rise(NULL);
    // wait_us(500);
    // if (BACK == 1){
    //     dpadMonitor.flags_set(6);
    // }
    // BACK.rise(back_IRQ);
}

void dpadDetection(){
    UP.rise(up_IRQ);
    // DOWN.rise(down_IRQ);
    LEFT.rise(left_IRQ);
    // RIGHT.rise(right_IRQ);
    // SEL.rise(sel_IRQ);
    // BACK.rise(back_IRQ);
}

void dpadMonitorMethod(){
    printf("D-Pad Monitoring Thread Starte\n");
    while (true) {
        ThisThread::flags_wait_any(0x7fffffff, false);
        int flag = ThisThread::flags_get();
        ThisThread::flags_clear(0x7fffffff);

        switch (flag) {
            case 1:
            printf("DPAD: UP\n");
            break;

            case 2:
            printf("DPAD: DOWN\n");
            break;

            case 3:
            printf("DPAD: LEFT\n");
            break;

            case 4:
            printf("DPAD: RIGHT\n");
            break;

            case 5:
            printf("DPAD: SEL\n");
            break;

            case 6:
            printf("DPAD: BACK\n");
            break;
        }
    }
}
