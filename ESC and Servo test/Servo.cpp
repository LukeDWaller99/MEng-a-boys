#include "Servo.h"

Servo::Servo(PinName pin) : _servo(pin) {
    setPWM();

}

void Servo::write(int angle){
    float clampedValue = normalise(angle);
    _normalised_angle = clampedValue;
    _angle = angle;
    _servo.pulsewidth_us(_normalised_angle);
}

void Servo::setPWM(int PWMValue){
   _servo.period_ms(PWMValue); 
}

int Servo::angle(){
    return _angle;
}

Servo& Servo::operator= (int angle){
    write(angle);
    return *this;
}


float Servo::normalise(int angle){

    float clampedValue = 0;
    float dividedValue = float(angle) / 360;

    if (dividedValue < MIN_ANGLE) {
        dividedValue = MIN_ANGLE;
    } else if (dividedValue > MAX_ANGLE) {
        dividedValue = MAX_ANGLE;
    }

    clampedValue = dividedValue * PWM_RANGE + PWM_OFFSET;
    return clampedValue;
}
