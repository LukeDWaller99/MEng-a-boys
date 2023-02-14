#include "Servo.h"

servo::servo(Pinname pin) : _servo(pin){
    setPWM();
}

void servo::write(float angle){
    float clampedValue = normalise(angle);
    _angle = clampedValue;
    _servo.pulsewidth_us(_angle);
}

void servo::setPWM(int PWMValue){
   _servo.period_ms(PWMValue); 
}

float servo::getAngle(){
    return _angle;
}

servo& servo::operator= (float angle){
    write(angle);
    return *this;
}

float servo::normalise(float speed){

    float clampedValue = 0;

    if (speed < MIN_THROTTLE) {
        speed = MIN_THROTTLE;
    } else if (speed > MAX_THROTTLE) {
        speed = MAX_THROTTLE;
    }

    clampedValue = speed * PWM_RANGE + PWM_OFFSET;
    return clampedValue;
}
