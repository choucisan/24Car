#include "Angle_PID.h"



// PID����
float Angle_Kp = -25.0f; // �ǶȻ���������//50��Ӧ2000���ٶ�
float Angle_Ki = 0.00f; // �ǶȻ���������5
float Angle_Kd = 0.0f; // �ǶȻ�΢������




float Angle_Error = 0, Angle_PreviousError = 0, Angle_Integral = 0;  //�Ƕ�PID  ƫ��  ��һ��ƫ��   ����
float Error, PreviousError = 0, Integral = 0;      //����PID


// ����ApplyOutput��һ������PID�����������ٶȵĺ���

float Angle_PID(float yaw, float target_Yaw)
{
//	if(target_Yaw >= 300 && yaw <= 100)
	if(fabs(target_Yaw - yaw) > 180) 
	{
		if(target_Yaw > yaw) Angle_Error = 360 - target_Yaw + yaw;
		else Angle_Error = -(360 + target_Yaw - yaw);
	}
	else Angle_Error  = yaw-target_Yaw;  //ƫ��
//	if(Angle_Error > 100) Angle_Error = 
//	if(Angle_Error < -200) Angle_Error = Angle_Error + 360;
//		if(Angle_Error > 200) Angle_Error = Angle_Error - 360;
	Angle_Integral += Angle_Error;  //����
	float derivative = Angle_Error - Angle_PreviousError;   //΢��
	float output = Angle_Kp * Angle_Error + Angle_Ki * Angle_Integral + Angle_Kd * derivative;
	Angle_PreviousError  = Angle_Error;
	if(output > 400) output = 400;
	return output;
}
// PID ����
float Speed_Kp = 10.0; // ��������
float Speed_Ki = 0.0; // ��������
float Speed_Kd = 0.0; // ΢������
// �ٶȻ� PID ������
float Speed_PID(int encoder_left, int encoder_right) {
    // ����ƽ���ٶ�
    static float speed_Error;
		static float Speed_PreviousError, Speed_Integral;
    // �����ٶ����
    speed_Error = encoder_left - encoder_right;

    // ������
    Speed_Integral += speed_Error;

    // ΢����
    float derivative = speed_Error - Speed_PreviousError;

    // PID �������
    float output = Speed_Kp * speed_Error + Speed_Ki * Speed_Integral + Speed_Kd * derivative;

    // ���������Χ
    if (output > 400) output = 400;
    if (output < -400) output = -400;

    // ������һ�ε����ֵ
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




