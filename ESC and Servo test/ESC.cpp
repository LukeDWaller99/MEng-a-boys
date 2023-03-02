#include "ESC.h"

ESC::ESC(PinName pin, int _calibrate) : _ESC(pin) {
    setPWM();
}

void ESC::write(float speed){
    float clampedValue = normalise(speed);
    _speed = clampedValue;
    _ESC.pulsewidth_us(_speed);
}

void ESC::setPWM(int PWMValue){
   _ESC.period_ms(PWMValue); 
}

float ESC::speed(){
    return _speed;
}

ESC& ESC::operator= (float speed){
    write(speed);
    return *this;
}

ESC& ESC::operator= (int on_off){
    return *this;
}

float ESC::normalise(float speed){

    float clampedValue = 0;

    if (speed < MIN_THROTTLE) {
        speed = MIN_THROTTLE;
    } else if (speed > MAX_THROTTLE) {
        speed = MAX_THROTTLE;
    }

    clampedValue = speed * PWM_RANGE + PWM_OFFSET;
    return clampedValue;
}
