#ifndef __ANGLE_PID_H
#define __ANGLE_PID_H

#include "A_include.h"


float Angle_PID(float yaw, float target_Yaw);
float Speed_PID(int encoder_left, int encoder_right);

extern float Error;




#endif
