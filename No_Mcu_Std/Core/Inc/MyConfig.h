#ifndef __MYCONFIG_H
#define __MYCONFIG_H

#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "Infrared.h"
#include "Encoder.h"
#include "Motor.h"
#include "Tim1.h"
#include "Tim3.h"
#include "PID.h"
#include "OLED.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h"

//====================== 物理与控制参数定义 ======================
#define RESOLUTION 13
#define RESOLUTION_TOTAL (13*4)
#define REDUCTION_RATIO  28
#define WHEEL_R  3.35f
#define CAR_LENGTH  20.35f
#define TWO_WHEEL_DISTANCE  13.9f
#define MOTOR_SPEED_MAX  500 
#define PID_COMPUTATION_PERIOD  10

//====================== 速度环测试专用参数 ======================
#define TEST_TARGET_SPEED_RPM 500.0f

//====================== 全局参数与标志位结构体 ======================
typedef struct
{
    long    Sigma_Motor1Pluse;
    long    Sigma_Motor2Pluse;
    int16_t UnitTime_Motor1Pluse;
    int16_t UnitTime_Motor2Pluse;
    float   Distance_Motor1Curret;
    float   Distance_TargetThreshold;
    int16_t Line_TempOut;
    uint8_t Send_Step;
} Param_InitTypeDef;

typedef struct
{
    uint8_t Is_EnMOTOR;
    uint8_t Start_Line;
    uint8_t Stop_Car;
} Flag_InitTypeDef;

//====================== 全局变量声明 (extern) ======================
extern Param_InitTypeDef Param;
extern Flag_InitTypeDef Flag;

//====================== 调试专用全局变量声明 (extern) ======================
extern volatile float g_Target_Speed_Debug;
extern volatile float g_Actual_Speed_Debug;
extern volatile int   g_Velocity_Out_Debug;
extern volatile float g_Distance_Debug;

//====================== 函数声明 ======================
void NVIC_Config(void);
void Velocity_Test_Start(void);
void Velocity_Test_Stop(void);
float VelocityRing_Out(void);

#endif