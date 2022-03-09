/**
 * @file L293D.h
 * 
 * @author Luke Waller
 */
#ifndef __L293D_H__
#define __L293D_H__

#define PWM_RANGE           20000.0f
#define MIN_THROTTLE        0.0f
#define MAX_THROTTLE        1.0f
#define DEFAULT_PWM_VALUE   20

/**
 * Includes
 */
#include <mbed.h>

class L293D {

public:

    /** Create an L293D object connected to specific pins
     *
     * @param pin1 DigitalOut pin for forwards motor operation
     * @param pin2 DigitalOut pin for reverse motor operation
     * @param enable PwmOut enable pin to turn motor on/off (used for speed control)
     */
    L293D(PinName pin1, PinName pin2, PinName enable);

    /** Sets direction of motor
     *
     * @param direction sets the direction of the motor (1 - forwards, -1 - reverse).
     */
    void setDirection(int direction = 0);

     /** Set the speed of the motor, normalised to it's full PWM range
     *
     * @param speed A normalised number to represent the full range of speeds.
     */
    void setSpeed(float speed);

    /** Turn the motor on */
    void run();

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

    /**  Read the current direction of the motor
     *
     * @param returns 1 for forwards, -1 for reverse.
     */
    int direction();

    /** Shorthand for writing the speed of the motor */
    L293D& operator= (float speed);

    /** Shorthand for setting the direction of the motor */
    L293D& operator= (int direction);

private:

    DigitalOut _motorA, _motorB;
    PwmOut _enable;
    float _speed;
    int _direction;

    /** Normalise the value between 0.0 and 1.0 */
    float normalise(float speed);

};


#endif