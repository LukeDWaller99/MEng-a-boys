#include "L298N.h"

L298N::L298N(PinName pin1, PinName pin2, PinName enable, int motorEnabled) : _motorA(pin1), _motorB(pin2), _enable(enable){
    _enable = motorEnabled;
    setDirection(0);
}

void L298N::setDirection(int direction){
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

void L298N::enableMotor(){_enable = 1;}

void L298N::disableMotor(){_enable = 0;}

int L298N::direction(){return _direction;}

void L298N::operator= (int direction){setDirection(direction);}

void L298N::operator= (bool enable){
    if (enable == true){
        enableMotor();
    } else {
        disableMotor();
    }
}