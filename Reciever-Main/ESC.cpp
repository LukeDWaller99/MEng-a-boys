#include "ESC.h"

ESC::ESC(PinName pin, int _calibrate) : _ESC(pin) {
    setPWM();

    if (_calibrate == 0) {
        connect();
    } else if (_calibrate == 1) {
        calibrate();
    }
}



void ESC::write(float speed){
    float clampedValue = normalise(speed);
    _p = speed;
    _ESC.pulsewidth_us(clampedValue);
}

void ESC::setPWM(int PWMValue){
   _ESC.period_ms(PWMValue); 
}

void ESC::connect(){
    write(MIN_THROTTLE);
    wait_us(ESC_CALIBRATE_TIME);
}

void ESC::calibrate(){
    write(MAX_THROTTLE);
    wait_us(ESC_CALIBRATE_TIME);
    write(MIN_THROTTLE);
    wait_us(ESC_CALIBRATE_TIME);
}

float ESC::speed(){
    return _p;
}

ESC& ESC::operator= (float speed){
    write(speed);
    return *this;
}

ESC& ESC::operator= (int on_off){
    if (on_off == 1){
        for(float i=0; i<1000; i++) {
            write(i/1000.0f);
            wait_us(2500);
        }
    } else if (on_off == 0) {
        for(float i=1000; i>0; i--) {
            write(i/1000.0f);
            wait_us(2500);
        }
    }
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
