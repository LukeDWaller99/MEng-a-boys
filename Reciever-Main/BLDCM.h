/**
 * @file BLDCM.h
 *
 * @author Luke Waller
*/
#ifndef __BLDCM_H__
#define __BLDCM_H__


/**
 * Includes
 */
#include <mbed.h>

class BLDCM {

public:

    /** Create a brushless DC motor object connected to the specified PwmOut pin
     *
     * @param pin PwmOut pin to connect to 
     */
    BLDCM(PinName pin);

    /** Set the speed of the motor, normalised to it's full range
     *
     * @param percent A normalised number 0.0-1.0 to represent the full range.
     */
    void write(float speed = 0.5);

    /**  Allows calibration of the range and angles for a particular Motor driver
     *
     * @param range Pulsewidth range from center (1.5ms) to maximum/minimum value in seconds
     * @param degrees Speed from middle to maximum/minimum position in degrees
     */
    void calibrate(float range = 0.0005, float pwmWidth = 45.0);

    /**  Read the current speed of the motor
     *
     * @param returns A normalised number 0.0-1.0  representing the full range.
     */
    float speed();


    /** Shorthand for writing the value of the motor */
    BLDCM& operator= (float speed);

    /** Shorthand for turning on the motor (allows ramp up and slow down) */
    BLDCM& operator= (int on_off);

    /** Shorthand for reading the speed of the motor */
    BLDCM& operator= (BLDCM& rhs);

protected:

    PwmOut BrushlessMotor;
    float _range;
    float _speed;
    float _p;

private:



};

#endif