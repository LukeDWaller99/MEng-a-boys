/**
 * @file Servo.h
 * 
 * @author Luke Waller
 */
#ifndef __SERVO_H__
#define __SERVO_H__

#define PWM_OFFSET          1000.0f
#define PWM_RANGE           1000.0f
#define ESC_CALIBRATE_TIME  4000000
#define MIN_ANGLE           0.0f
#define MAX_ANGLE           300.0f
#define DEFAULT_PWM_VALUE   20

/**
 * Includes
 */
#include <mbed.h>

class Servo {

public:

    /** Create a Servo motor object connected to the specified PwmOut pin.
     *
     * @param pin PwmOut pin to connect to. 
     */
    Servo(PinName pin);

    /** Set the angle of the motor, normalised to it's full range
     *
     * @param angle A normalised number 0.0-1.0 to represent the full range.
     */
    void write(int angle);

    /** Set the period of the PWM pin output
    *
    * @param PWMValue PWM output period (ms)
    */
    void setPWM(int PWMValue = DEFAULT_PWM_VALUE);

    /**  Read the current angle of the motor
     *
     * @param returns the angle of the motor
     */
    int angle();


    /** Shorthand for writing the value of the motor */
    Servo& operator= (int angle);

private:

    PwmOut _servo;
    float _range;
    int _angle;
    float _normalised_angle;

    /** Normalise the value between 0.0 and 1.0 */
    float normalise(int angle);

};

#endif