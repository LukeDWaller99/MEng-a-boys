#include "L293D.h"

L293D::L293D(PinName pin1, PinName pin2, PinName enable) : _motorA(pin1), _motorB(pin2), _enable(enable) {
    setPWM();

}

void L293D::setDirection(int direction){
    if (direction == 1){ // forwards
        _direction = direction;
    } else if (direction == -1) { // reverse
        _direction = direction;
    } else {
        _direction = 0;
    }
}

void L293D::setSpeed(float speed){
    float clampedValue = normalise(speed);
    _speed = clampedValue;
    _enable.pulsewidth_us(_speed);
}

void L293D::run(){
    if (_direction == 1) {
        _motorB = 0;
        _motorA = 1;
    } else if (_direction == -1) {
        _motorA = 0;
        _motorB = 1;
    } else {
        _motorA = 0;
        _motorB = 0;
    }
}

void L293D::setPWM(int PWMValue){
    _enable.period_ms(PWMValue);
}

float L293D::speed(){
    return _speed;
}

int L293D::direction(){
    return _direction;
}

L293D& L293D::operator= (float speed){
    setSpeed(speed);
    return *this;
}

L293D& L293D::operator= (int direction){
    setDirection(direction);
    return *this;
}

float L293D::normalise(float speed){

    float clampedValue = 0;

    if (speed < MIN_THROTTLE) {
        speed = MIN_THROTTLE;
    } else if (speed > MAX_THROTTLE) {
        speed = MAX_THROTTLE;
    }

    clampedValue = speed * PWM_RANGE;
    return clampedValue;
}