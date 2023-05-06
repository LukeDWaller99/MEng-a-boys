#include "mbed.h"
#include "LCD.h"
#include "L432KC_Hardware.h"
// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


char foo[20] = "noah smells";
int main()
{
    LCD lcd(LCD_RS,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    lcd.put_char('a');
    lcd.clear_LCD();
    lcd.put_char_array(foo);
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
