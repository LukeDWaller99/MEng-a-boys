/**
 * @file ESC.h
 * 
 * @author Luke Waller
 */
#ifndef __ESC_H__
#define __ESC_H__

#define PWM_OFFSET          1000.0f
#define PWM_RANGE           1000.0f
#define ESC_CALIBRATE_TIME  4000000
#define MIN_THROTTLE        0.0f
#define MAX_THROTTLE        1.0f
#define DEFAULT_PWM_VALUE   20

/**
 * Includes
 */
#include <mbed.h>

class ESC {

public:

    /** Create a brushless DC motor object connected to the specified PwmOut pin.
     *
     * @param pin PwmOut pin to connect to. 
     * @param calibrate Determines whether or not to calibrate the ESC.
     */
    ESC(PinName pin, int calibrate = 0);

    /** Set the speed of the motor, normalised to it's full range
     *
     * @param speed A normalised number 0.0-1.0 to represent the full range.
     */
    void write(float speed);

    /** Set the period of the PWM pin output
    *
    * @param PWMValue PWM output period (ms)
    */
    void setPWM(int PWMValue = DEFAULT_PWM_VALUE);

    /**  Read the current speed of the motor
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    float speed();


    /** Shorthand for writing the value of the motor */
    ESC& operator= (float speed);

    /** Shorthand for turning on the motor (allows ramp up and slow down) */
    ESC& operator= (int on_off);

private:

    PwmOut _ESC;
    float _range;
    float _speed;

    /** Normalise the value between 0.0 and 1.0 */
    float normalise(float speed);

    /** Pair the ESC and the board */
    void connect();

    /** Calibrate the ESC to the range of the microcontroller */
    void calibrate();

};

#endif