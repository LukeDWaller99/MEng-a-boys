/**
 * @file L293D.h
 * 
 * @author Luke Waller
 */
#ifndef __L298N_H__
#define __L298N_H__

#include "PinNames.h"
#define PWM_RANGE           20000.0f
#define MIN_THROTTLE        0.0f
#define MAX_THROTTLE        1.0f
#define DEFAULT_PWM_VALUE   20

/**
 * Includes
 */
#include <mbed.h>

class L298N {

public:

    /** Create an L293D object connected to specific pins
     *
     * @param pin1 DigitalOut pin for forwards motor operation
     * @param pin2 DigitalOut pin for reverse motor operation
     * @param enable DigitalOut to enable and disable motor
     * @param motorEnabled int to set intial state of the motor
     */
    L298N(PinName pin1, PinName pin2, PinName enable, int motorEnabled = 0);

    /** Sets direction of motor
     *
     * @param direction sets the direction of the motor (1 - forwards, -1 - reverse).
     */
    void setDirection(int direction);

    /** Enables the motor */
    void enableMotor();

    /** Disables the motor */
    void disableMotor();

    /**  Read the current direction of the motor
     *
     * @param returns 1 for forwards, -1 for reverse.
     */
    int direction();

    /** Shorthand for setting the direction of the motor */
    void operator= (int direction);

    /** Shorthand for enabling and disabling the motor */
    void operator= (bool enabled);

private:

    DigitalOut _motorA, _motorB, _enable;
    float _speed;
    int _direction;

};


#endif