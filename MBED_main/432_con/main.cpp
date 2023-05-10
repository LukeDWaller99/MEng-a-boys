#include "mbed.h"
#include "LCD.h"
#include "L432KC_Hardware.h"
#include "ThisThread.h"
// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


// //SPI spi(MOSI, MISO, SCK);
// //this one must be set as slave
// SPISlave spi(MOSI, MISO, SCK, SP_D7);

// char foo[20] = "noah smells";
// int main()
// {   
//     printf("Starting board...\n");
//     wait_us(500);
//     //spi business
//     int counter = 1;
//     spi.format(8,3); //8-bit mode
//     spi.frequency(1000000); //1MHz
//     //Test SPI responses
//     int reply = 99;
//     spi.reply(reply);
//     spi.reply(reply);

//     printf("SPI Device Response: %d\n", reply);

//     LCD lcd(LCD_RS,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
//     // Initialise the digital pin LED1 as an output
//     DigitalOut led(LED1);
//     lcd.put_char('a');
//     lcd.clear_LCD();
//     lcd.put_char_array(foo);
//     while (true) {
//         if (spi.receive()) {
//             int valueFromMaster = spi.read();
//             printf("Counter: %d . SPI Master Incoming: %d.\n", counter++, valueFromMaster);
//             spi.reply(++reply);
//             printf("Recieved: %d . Next Reply: %d \n", valueFromMaster, reply);
//         }
//         // led = !led;
//         // ThisThread::sleep_for(BLINKING_RATE);
//     }
// }
