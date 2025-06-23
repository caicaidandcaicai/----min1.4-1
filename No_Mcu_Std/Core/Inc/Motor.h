#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"                  // Device header
#include "sys.h"

#define M_left_IN1   PBout(13)
#define M_left_IN2   PBout(12)
#define M_right_IN3  PBout(14)
#define M_right_IN4  PBout(15)

#define PWM_MAX 3599

typedef enum
{
	FORWARD,
	BACK,
	STOP,
}MotorDIR_Choose;

void Motor_GPIO_Init(void);
void Load_Motor_PWM(int MOTOR1_PWM,int MOTOR2_PWM) ;
void Motor_Right_DIR(MotorDIR_Choose DT);
void Motor_Left_DIR(MotorDIR_Choose DT);
void set_motor_enable(void);
void set_motor_disable(void);

#endif
