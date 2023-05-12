#include "InterruptIn.h"
#include "L432KC_Hardware.h"
#include "LCD.h"
#include "TextLCD.h"
#include "ThisThread.h"
#include "mbed.h"


#define BLINKING_RATE 500ms

InterruptIn UP(D_UP);
InterruptIn DOWN(D_DOWN);
InterruptIn LEFT(D_LEFT);
InterruptIn RIGHT(D_RIGHT);
// InterruptIn SEL(D_SEL); //IRQ CHANNEL CONFLICT
// InterruptIn BACK(D_BACK); //IRQ CHANNEL CONFLICT

Thread dpadMonitor;

Mutex dupLock, ddownLock, dleftLock, drightLock;

void dpadMonitorMethod();
void dpadDetection();
void up_IRQ();
void down_IRQ();
void left_IRQ();
void right_IRQ();
void sel_IRQ();
void back_IRQ();

SPISlave myspi(mosi, miso, SCK, CS); // mosi, miso, sclk, nSS
// TextLCD LCD(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, TextLCD::LCD16x2);
const char message[] = "hi\n";
int main() {
  printf("L432 Controller Board Started\n");

  myspi.frequency(1000000);
  myspi.format(8, 0);
  myspi.reply(0x5A);
  TextLCD LCD(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

    LCD.putc('c');
    
  while (1) {
    if (myspi.receive()) {
      int data = myspi.read();
      printf("Received %x2\n", data);
      myspi.reply(data); // Read byte from master and transmit it at the next
                         // transaction
    }
  }
}

void up_IRQ() {
  UP.rise(NULL);
  wait_us(500);
  if (UP == 1) {
    dpadMonitor.flags_set(1);
  }
  UP.rise(up_IRQ);
}

void down_IRQ() {
  DOWN.rise(NULL);
  wait_us(500);
  if (DOWN == 1) {
    dpadMonitor.flags_set(2);
  }
  DOWN.rise(down_IRQ);
}

void left_IRQ() {
  LEFT.rise(NULL);
  wait_us(500);
  if (LEFT == 1) {
    dpadMonitor.flags_set(3);
  }
  LEFT.rise(left_IRQ);
}

void right_IRQ() {
  RIGHT.rise(NULL);
  wait_us(500);
  if (RIGHT == 1) {
    dpadMonitor.flags_set(4);
  }
  RIGHT.rise(right_IRQ);
}

void sel_IRQ() {
  // SEL.rise(NULL);
  // wait_us(500);
  // if (SEL == 1){
  //     dpadMonitor.flags_set(5);
  // }
  // SEL.rise(sel_IRQ);
}

void back_IRQ() {
  // BACK.rise(NULL);
  // wait_us(500);
  // if (BACK == 1){
  //     dpadMonitor.flags_set(6);
  // }
  // BACK.rise(back_IRQ);
}

void dpadDetection() {
  UP.rise(up_IRQ);
  DOWN.rise(down_IRQ);
  LEFT.rise(left_IRQ);
  RIGHT.rise(right_IRQ);
  // SEL.rise(sel_IRQ);
  // BACK.rise(back_IRQ);
}

void dpadMonitorMethod() {
  printf("D-Pad Monitoring Thread Starte\n");
  while (true) {
    ThisThread::flags_wait_any(0x7fffffff, false);
    int flag = ThisThread::flags_get();
    ThisThread::flags_clear(0x7fffffff);

    switch (flag) {
    case 1:
      printf("DPAD: UP\n");
      dupLock.trylock_until(Kernel::Clock::now() + 1s);
      //METHOD
      dupLock.unlock();
      break;

    case 2:
      printf("DPAD: DOWN\n");
      ddownLock.trylock_until(Kernel::Clock::now() + 1s);
      //METHOD
      ddownLock.unlock();
      break;

    case 3:
      printf("DPAD: LEFT\n");
      dleftLock.trylock_until(Kernel::Clock::now() + 1s);
      //METHOD
      dleftLock.unlock();
      break;

    case 4:
      printf("DPAD: RIGHT\n");
      drightLock.trylock_until(Kernel::Clock::now() + 1s);
      //METHOD
      drightLock.unlock();
      break;

    //THESE DONT WORK
    // case 5:
    //   printf("DPAD: SEL\n");
    //   break;

    // case 6:
    //   printf("DPAD: BACK\n");
    //   break;
    }
  }
}
