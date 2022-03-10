#include "L293D.h"

L293D::L293D(PinName pin1, PinName pin2, PinName enable, int motorEnabled) : _motorA(pin1), _motorB(pin2), _enable(enable){
    _enable = motorEnabled;
    setDirection(0);
}

void L293D::setDirection(int direction){
    if (direction == 1){ // forwards
        _direction = direction;
        _motorB = 0;
        _motorA = 1;
    } else if (direction == -1) { // reverse
        _direction = direction;
        _motorA = 0;
        _motorB = 1;
    } else {
        _direction = 0;
        _motorA = 0;
        _motorB = 0;
    }
}

void L293D::enableMotor(){_enable = 1;}

void L293D::disableMotor(){_enable = 0;}

int L293D::direction(){return _direction;}

void L293D::operator= (int direction){setDirection(direction);}

void L293D::operator= (bool enable){
    if (enable == true){
        enableMotor();
    } else {
        disableMotor();
    }
}