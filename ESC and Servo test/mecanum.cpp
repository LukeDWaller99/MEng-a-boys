#include "mecanum.h"

float driveLeftFront(int angle, float speed){
    double radian_angle = angle * (PI/180);
    double angleSin = sin(angle - (PI/4));
    double output = angleSin * speed;
    return output;
}

float driveRightFront(int angle, float speed){
    double radian_angle = angle * (PI/180);
    double angleSin = sin(angle + (PI/4));
    double output = angleSin * speed;
    return output;
}

float driveLeftRear(int angle, float speed){
    double radian_angle = angle * (PI/180);
    double angleSin = sin(angle + (PI/4));
    double output = angleSin * speed;
    return output;
}

float driveRightRear(int angle, float speed){

    double radian_angle = angle * (PI/180);
    double angleSin = sin(angle - (PI/4));
    double output = angleSin * speed;
    return output;
}


int cartToPolarAngle(float xCoord, float yCoord){

    double angleInRads = 0.0;
    double angleInDeg = 0.0;
    int roundedAngleInDeg = 0;

    angleInRads = atan2(yCoord, xCoord);
    angleInDeg = angleInRads * (180 / PI);
    roundedAngleInDeg = round(angleInDeg); 
    if (roundedAngleInDeg < 0) {roundedAngleInDeg += 360;}
    return roundedAngleInDeg;
}

float cartToPolarSpeed(float xCoord, float yCoord){
    float vectoredSpeed = 0.0f;
    vectoredSpeed = sqrt((xCoord*xCoord)+(yCoord*yCoord));
    return vectoredSpeed;
}