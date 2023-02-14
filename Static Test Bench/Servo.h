/**
 * @file ESC.h
 * 
 * @author Luke Waller
 */
#ifndef __Servo_H__
#define __Servo_H__

#define PWM_OFFSET          1000.0f
#define PWM_RANGE           1000.0f
#define MIN_ANGLE           0.0f
#define MAX_ANGLE           1.0f
#define DEFAULT_PWM_VALUE   20

/**
 * Includes
 */
#include <mbed.h>

class servo{

public:

    /** Create a servo motor object connected to the specified PwmOut pin.
     *
     * @param pin PwmOut pin to connect to. 
     */
     servo(PinName pin);

    /** Set the speed of the motor, normalised to it's full range
     *
     * @param speed A normalised number 0.0-1.0 to represent the full range.
     */
    void write(float angle);

    /** Set the period of the PWM pin output
    *
    * @param PWMValue PWM output period (ms)
    */
    void setPWM(int PWMValue = DEFAULT_PWM_VALUE);

    /**  Read the current angle of the motor
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    float getAngle();

    /** Shorthand for writing the value of the motor */
    servo& operator= (float angle);


private:

    PwmOut _servo;
    float _range;
    float _angle;

    /** Normalise the value between 0.0 and 1.0 */
    float normalise(float angle);

};

#endif
