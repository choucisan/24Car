#include "Angle_PID.h"



// PID参数
float Angle_Kp = -25.0f; // 角度环比例增益//50对应2000的速度
float Angle_Ki = 0.00f; // 角度环积分增益5
float Angle_Kd = 0.0f; // 角度环微分增益




float Angle_Error = 0, Angle_PreviousError = 0, Angle_Integral = 0;  //角度PID  偏差  上一次偏差   积分
float Error, PreviousError = 0, Integral = 0;      //行走PID


// 假设ApplyOutput是一个根据PID输出调整电机速度的函数

float Angle_PID(float yaw, float target_Yaw)
{
//	if(target_Yaw >= 300 && yaw <= 100)
	if(fabs(target_Yaw - yaw) > 180) 
	{
		if(target_Yaw > yaw) Angle_Error = 360 - target_Yaw + yaw;
		else Angle_Error = -(360 + target_Yaw - yaw);
	}
	else Angle_Error  = yaw-target_Yaw;  //偏差
//	if(Angle_Error > 100) Angle_Error = 
//	if(Angle_Error < -200) Angle_Error = Angle_Error + 360;
//		if(Angle_Error > 200) Angle_Error = Angle_Error - 360;
	Angle_Integral += Angle_Error;  //积分
	float derivative = Angle_Error - Angle_PreviousError;   //微分
	float output = Angle_Kp * Angle_Error + Angle_Ki * Angle_Integral + Angle_Kd * derivative;
	Angle_PreviousError  = Angle_Error;
	if(output > 400) output = 400;
	return output;
}
// PID 参数
float Speed_Kp = 10.0; // 比例增益
float Speed_Ki = 0.0; // 积分增益
float Speed_Kd = 0.0; // 微分增益
// 速度环 PID 控制器
float Speed_PID(int encoder_left, int encoder_right) {
    // 计算平均速度
    static float speed_Error;
		static float Speed_PreviousError, Speed_Integral;
    // 计算速度误差
    speed_Error = encoder_left - encoder_right;

    // 积分项
    Speed_Integral += speed_Error;

    // 微分项
    float derivative = speed_Error - Speed_PreviousError;

    // PID 控制输出
    float output = Speed_Kp * speed_Error + Speed_Ki * Speed_Integral + Speed_Kd * derivative;

    // 限制输出范围
    if (output > 400) output = 400;
    if (output < -400) output = -400;

    // 更新上一次的误差值
    Speed_PreviousError = speed_Error;

    return output;
}




float MPU_change(float zhi)
{
	if (zhi >= 180)
	{
		zhi = zhi-360;
	}
	if (zhi <= -180)
	{
		zhi = zhi+360;
	}
	return zhi;
}




