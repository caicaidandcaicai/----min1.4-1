#include "MyConfig.h"
#include "motor.h"
#include "PID.h"
#include <math.h>
#include <stdlib.h>

//====================== 全局变量定义 ======================
Param_InitTypeDef Param;
Flag_InitTypeDef Flag;

//====================== 调试专用全局变量定义 ======================
volatile float g_Target_Speed_Debug = 0.0f;
volatile float g_Actual_Speed_Debug = 0.0f;
volatile int   g_Velocity_Out_Debug = 0;
volatile float g_Distance_Debug = 0.0f;

void NVIC_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void Velocity_Test_Start(void)
{
    PID_Param_Init();
    Param.Sigma_Motor1Pluse = 0;
    Param.Sigma_Motor2Pluse = 0;
    
    Flag.Start_Line = 1;
    Motor_Left_DIR(FORWARD);
    Motor_Right_DIR(FORWARD);
    
    set_motor_enable();
}

void Velocity_Test_Stop(void)
{
    Flag.Start_Line = 0;
    set_motor_disable();
}

float VelocityRing_Out(void)
{
    float actual_rpm = ((float)Param.UnitTime_Motor1Pluse /  
                       ((float)RESOLUTION_TOTAL * (float)REDUCTION_RATIO)) * 
                       (60000.0f / (float)PID_COMPUTATION_PERIOD);
    
    g_Actual_Speed_Debug = actual_rpm;
    float output_pwm = VelocityRing_PID_Realize(actual_rpm);
    return output_pwm;
}

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

        Param.UnitTime_Motor1Pluse = Read_Pulse(2);
        Param.UnitTime_Motor2Pluse = -Read_Pulse(4);
        Param.Sigma_Motor1Pluse += Param.UnitTime_Motor1Pluse;
        
        g_Distance_Debug = (Param.Sigma_Motor1Pluse / (float)(RESOLUTION_TOTAL * REDUCTION_RATIO)) * (2.0f * 3.14159f * WHEEL_R);

        if(Flag.Start_Line == 1)
        {
            PID.Velocity_Target_Val = TEST_TARGET_SPEED_RPM;
            g_Target_Speed_Debug = PID.Velocity_Target_Val;

            PID.Velocity_Out = (int)VelocityRing_Out();
            g_Velocity_Out_Debug = PID.Velocity_Out;

            Load_Motor_PWM(PID.Velocity_Out, PID.Velocity_Out);
        }
        else
        {
            set_motor_disable();
        }
    }
}