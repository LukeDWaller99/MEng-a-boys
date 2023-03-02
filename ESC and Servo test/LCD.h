/**
 * @file LCD.h
 *
 * @author Luke Waller
 * 
 * @section LICENSE
 *
 * Copyright (c) 2022 Luke Waller
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * @section DESCRIPTION
 *
 * LCD Display using a HD4478 driver chip
 *
 */

#ifndef __LCD_H__
#define __LCD_H__

/**
 * Includes
 */
#include "PinNames.h"
#include "mbed.h"

/**
 * Defines
 */
#define LCD_LINE_1                          0x80
#define LCD_LINE_2                          0xc0
#define LCD_FUNCTION_8_BIT_1_LINE_5x7_DOTS  0x30 // Function set: 1 Line, 8-bit, 5x7 dots
#define LCD_FUNCTION_8_BIT_2_LINE_5x7_DOTS  0x38 // Function set: 2 Line, 8-bit, 5x7 dots
#define LCD_FUNCTION_4_BIT_1_LINE_5x7_DOTS  0x20 // Function set: 1 Line, 4-bit, 5x7 dots
#define LCD_FUNCTION_4_BIT_2_LINE_5x7_DOTS  0x28 // Function set: 2 Line, 4-bit, 5x7 dots
#define LCD_ENTRY_MODE_AUTO_INCREMENT       0x06 // Entry mode, auto increment with no shift
#define LCD_DISP_OFF_CURSOR_OFF             0x08 // Display off, Cursor off
#define LCD_DISP_ON_CURSOR_ON               0x0E // Display on, Cursor on
#define LCD_DISP_ON_CURSOR_OFF              0x0C // Display on, Cursor off
#define LCD_DISP_ON_CURSOR_BLINKING         0x0F // Display on, Cursor blinking
#define LCD_SHIFT_DISP_LEFT                 0x18 // Shift entire display left
#define LCD_SHIFT_DISP_RIGHT                0x1C // Shift entire display right
#define LCD_MOVE_CURSOR_LEFT                0x10 // Move cursor left by one character
#define LCD_MOVE_CURSOR_RIGHT               0x14 // Move cursor right by one character
#define LCD_CLEAR                           0x01 // Clears LCD

/**
 * LCD Display using a HD4478 driver chip
 */
class LCD{

    public:
    
    /**
     * @brief Constructor 4-bit
     * 
     * @param RS mbed pin to use for register select 
     * @param RW mbed pin to use for read/write select 
     * @param Enable mbed pin to use for enable select
     * @param D4 mbed pin to use for data line 4
     * @param D5 mbed pin to use for data line 5
     * @param D6 mbed pin to use for data line 6 
     * @param D7 mbed pin to use for data line 7 
     */
    LCD(PinName RS, PinName RW, PinName Enable, PinName D4, PinName D5, PinName D6, PinName D7);
    
    /**
     * @brief Constructor 8-bit
     *
     * @param RS mbed pin to use for 
     * @param RW mbed pin to use for 
     * @param Enable mbed pin to use for 
     * @param D0 mbed pin to use for data line 0
     * @param D1 mbed pin to use for data line 1
     * @param D2 mbed pin to use for data line 2 
     * @param D3 mbed pin to use for data line 3 
     * @param D4 mbed pin to use for data line 4 
     * @param D5 mbed pin to use for data line 5 
     * @param D6 mbed pin to use for data line 6 
     * @param D7 mbed pin to use for data line 7 
     */
    LCD(PinName RS, PinName RW, PinName Enable, PinName D0, PinName D1, PinName D2, PinName D3, PinName D4, PinName D5, PinName D6, PinName D7);

    /**
     * @brief Send data to the control register of the LCD display
     * 
     * @param cmd 
     */
    void LCD_cmd(unsigned char cmd);

    /** 
     * Set Cursor on LCD Display
     * 
     * @param column selects column to write to
     * @param row selects row to write to
     */
    void cursor_Set(int column, int row);

    /**
     * @brief Sends char to the LCD
     * 
     * @param data 
     */
    void put_char(unsigned char data);

    /**
     * Outputs char to the LCD
     *
     * @param data 
     * @param length length of char array being outputted (default 16)
     */
    void put_char_array(char *data, int length=16);
 
    /**
     * @brief Decimal value to be written to the display
     * 
     * @param decimal_val 
     */
    void put_integer(int decimal_val);

    /**
     * @brief Float value to be written to the display  
     * 
     * @param float_val 
     * @param precision 
     */
    void put_float(float float_val, int precision=3);

    /**
     * @brief Boolean value to be written to the display
     * 
     * @param value 
     */
    void put_bool(bool value);

    /**
     * @brief Clear the LCD
     * 
     */
    void clear_LCD();

    /**
     * @brief Move LCD display left by 1 block
     * 
     */
    void move_disp_left();

    /**
     * @brief Move LCD display right by 1 block
     * 
     */
    void move_disp_right();

    /**
     * @brief Move LCD cursor left by 1 block
     * 
     */
    void move_cursor_left();

    /**
     * @brief Move LCD cursor right by 1 block
     * 
     */
    void move_cursor_right();

    void cursor_on();

    void cursor_off();

    void cursor_blinking();

    /** Shorthand for writing a decimal value to the LCD */
    void operator=(int value);

    /** Shorthand for writing a float value to the LCD */
    void operator=(float value);

    /** Shorthand for writing a char to the LCD */
    void operator=(char character);

    /** Shorthand for writing a long to the LCD */
    void operator=(long value);

    /** Shorthand for writing a double to the LCD */
    void operator=(double value);

    /** Shorthand for writing a boolean value to the LCD */
    void operator=(bool value);

    /** Shorthand for moving display left */
    void operator<<(int number);

    /** Shorthand for moving display right */
    void operator>>(int number);

    /** Shorthand for moving cursor left */
    void operator<(int number);

    /** Shorthand for moving cursor right */
    void operator>(int number);

    private:

    /**
     * @brief Waits for the LCD to be ready to receive data
     * 
     */
    void wait_busy(void);

    /**
     * @brief Sends data to the LCD
     * 
     */
    void strobe_LCD(void);

    DigitalOut _rs, _rw, _enable;
    BusInOut _data;
    int _mode = 0;

};

#endif
