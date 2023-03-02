/**
 * @file mecanum.h
 * 
 * @author Luke Waller
 */
#ifndef __MECANUM_H__
#define __MECANUM_H__

/**
 * Includes
 */
#include <algorithm>
#include <cmath>
#include <math.h>

#define PI 3.14159f
#define theta 90
#define power 10
#define turn 0

float driveLeftFront(int angle, float speed);
float driveRightFront(int angle, float speed);
float driveLeftRear(int angle, float speed);
float driveRightRear(int angle, float speed);

int cartToPolarAngle(float xCoord, float yCoord);
float cartToPolarSpeed(float xCoord, float yCoord);

#endif