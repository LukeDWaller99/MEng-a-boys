#include "BLDCM.h"

static float clampVal(float value, float minVal, float maxVal){
    if (value <= minVal){
        return minVal;
    } else if (value >= maxVal) {
        return maxVal;
    } else {
        return value;
    }
}


BLDCM::BLDCM(PinName pin) : BrushlessMotor(pin) {
    calibrate();
    write();
}

void BLDCM::write(float speed){
    float offsetVal = _range * 2.0 * (speed - 0.5);
    BrushlessMotor.pulsewidth(0.0015 + clampVal(offsetVal, -_range, _range));
    _p = clampVal(speed, 0.0, 1.0);
}

void BLDCM::calibrate(float range, float pwmWidth){
    _range = range;
    _speed = pwmWidth;
}

float BLDCM::speed(){
    return _p;
}

BLDCM& BLDCM::operator= (float speed){
    write(speed);
    return *this;
}

BLDCM& BLDCM::operator= (int on_off){
    if (on_off == 1){
        for(int i=0; i<100; i++) {
            write(i/100.0);
            wait_us(1000);
        }
    } else if (on_off == 0) {
        for(int i=100; i>0; i--) {
            write(i/100.0);
            wait_us(1000);
        }
    }
    return *this;
}

BLDCM& BLDCM::operator= (BLDCM& rhs){
    write(rhs.speed());
    return *this;
}