/**
 * @file Buzzer.h
 *
 * @author Luke Waller
*/

#ifndef __BUZZER_H__
#define __BUZZER_H__

/**
 * Includes
 */
#include <mbed.h>


/**
 * Defines
 */
#define BUZZER_PIN PB_13

class Buzzer {

public:

    typedef enum {
        LOWER, 
        MIDDLE, 
        HIGHER
        } OCTAVE;

    Buzzer(PinName pin = BUZZER_PIN);
    void setNote(const char* note = "C", OCTAVE octave=MIDDLE); 
    void buzz(float amount = 0.5f);
    void stop();

    void operator = (const char* note);
    void operator = (int on_off);
    void operator = (float time);

    void chime(int delay = 100000, const char* note1 = "C", const char* note2 = "D", const char* note3 = "E", OCTAVE octave = HIGHER);

protected:

    PwmOut buzzer;
    double notePeriod(const char* note, OCTAVE octave=MIDDLE);

private:

    uint8_t noteOffset(const char *noteStr);

    double frequencyOfNote[12] = {
        220.0, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3
    };

};

#endif