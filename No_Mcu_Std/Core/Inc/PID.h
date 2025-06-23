#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"                  // Device header


typedef struct
{	//位置环
	float Location_Kp;//位置环Kp
	float Location_Ki;//位置环Ki
	float Location_Kd;//位置环Kd
	float Location_Error;	//位置环的偏差
	float Location_ErrorLast;	//位置环上一次的偏差
	float Location_Integral;	//位置环的积分值
	float Location_Target_Val;	//位置环的期望值
	float Location_Actual_Val;  //位置环的实际值
	int   Location_Out;//位置环的输出
	
	//速度环
	float Velocity_Kp;//速度环Kp
	float Velocity_Ki;//速度环Ki
	float Velocity_Kd;//速度环Kd
	float Velocity_Error;	//速度环的偏差
	float Velocity_ErrorLast;	//速度环的上一次的偏差
	float Velocity_Integral;	//速度环的积分值
	float Velocity_Target_Val;	//速度环的期望值
	float Velocity_Actual_Val;  //速度环的实际值
	int   Velocity_Out;//速度环的输出
	
}PID_InitTypedef; 


extern PID_InitTypedef PID;
void PID_Param_Init(void);
float LocationRing_PID_Realize(float Location_Actual_Val);
float VelocityRing_PID_Realize(float Velocity_Actual_Val);
#endif
