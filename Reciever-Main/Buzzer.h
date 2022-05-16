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

class Buzzer {

public:

    typedef enum {
        LOWER, 
        MIDDLE, 
        HIGHER
        } OCTAVE;


    /** Create a Buzzer Object connected to a specific PwmOut pin.
     *
     * @param pin PwnOut pin to connect to.
     */
    Buzzer(PinName pin);

    /** Set the note of the Buzzer
     *
     * @param note = "C" sets the note of the Buzzer
     * @param ocatave = MIDDLE sets the ocatave range of the note
     */
    void setNote(const char* note = "C", OCTAVE octave=MIDDLE); 

    /** Set the duty cycle for the buzzer
     *
     *@param amount Sets the duty cycle of the pwm signal
     */
    void buzz(float amount = 0.5f);

    /** Stops The Buzzer */
    void stop();

    /** Disables the buzzer (stops it from sounding even if it is turned on) */
    void disable();

    /** Enables the buzzer (does not turn the buzzer on) */
    void enable();

    /** Shorthand for setting the note the buzzer emits */
    void operator = (const char* note);

    /** Shorthand for setting the buzzer on or off */
    void operator = (int on_off);

    /** Shorthand for setting PWM duty cycle of the buzzer */
    void operator = (float time);

    /** Shorthand for enabling and disabling the motor */
    void operator = (bool enabled);

    /** Set the buzzer to play three notes in a row
     *
     *@param delay = 100000 - time delay between notes
     *@param note1 = "C" - note for the first tone of the chime
     *@param note2 = "D" - note for the second tone of the chime
     *@param note3 = "E" - note for the third tone of the chime
     *@param octave = HIGHER - octave for the notes of the chime
     */ 
    void chime(int delay = 100000, const char* note1 = "C", const char* note2 = "D", const char* note3 = "E", OCTAVE octave = HIGHER);

protected:

    PwmOut buzzer;
    double notePeriod(const char* note, OCTAVE octave=MIDDLE);

private:

    uint8_t noteOffset(const char *noteStr);

    bool _enabled;

    double frequencyOfNote[12] = {
        220.0, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3
    };

};

#endif