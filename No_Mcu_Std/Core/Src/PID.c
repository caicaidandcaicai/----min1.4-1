#include "PID.h"

PID_InitTypedef PID;

void PID_Param_Init(void)
{
    PID.Location_Kp = 0.0f;
    PID.Location_Ki = 0.0f;
    PID.Location_Kd = 0.0f;
    PID.Location_Integral = 0.0f;
    PID.Location_Error = 0.0f;
    PID.Location_ErrorLast = 0.0f;
    PID.Location_Out = 0;

    /* �ٶȻ���PID - ��������Ҫ�����Ĳ��� */
    PID.Velocity_Target_Val = 0.0f;
    PID.Velocity_Actual_Val = 0.0f;
    
    // ��������㡿Kp��Ҫһ�����õ��ת������ֵ��2.0��һ����������
    PID.Velocity_Kp = 51.0f;  
    // ��������㡿Ki��Kd�ڳ��β���ʱ����Ϊ0
    PID.Velocity_Ki = 0.5f; 
    PID.Velocity_Kd = 0.5f; 
    
    PID.Velocity_Integral = 0.0f;
    PID.Velocity_Error = 0.0f;
    PID.Velocity_ErrorLast = 0.0f;
    PID.Velocity_Out = 0;
}

float LocationRing_PID_Realize(float Location_Actual_Val)
{
    return 0.0f; // �ڴ˲����в�ʹ��
}

float VelocityRing_PID_Realize(float Velocity_Actual_Val)
{
    float output;
    PID.Velocity_Error = PID.Velocity_Target_Val - Velocity_Actual_Val;

    if((PID.Velocity_Error < 0.5f) && (PID.Velocity_Error > -0.5f))
    {
        PID.Velocity_Error = 0.0f;
    }

    PID.Velocity_Integral += PID.Velocity_Error;

    if(PID.Velocity_Integral > 10000) PID.Velocity_Integral = 10000;
    if(PID.Velocity_Integral < -10000) PID.Velocity_Integral = -10000;

    output = PID.Velocity_Kp * PID.Velocity_Error 
           + PID.Velocity_Ki * PID.Velocity_Integral 
           + PID.Velocity_Kd * (PID.Velocity_Error - PID.Velocity_ErrorLast);
    
    PID.Velocity_ErrorLast = PID.Velocity_Error;
    return output;
}