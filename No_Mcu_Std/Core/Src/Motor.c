#include "motor.h"
#include "MyConfig.h"
#include <stdlib.h>

extern Flag_InitTypeDef Flag;

void Motor_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Motor_Left_DIR(MotorDIR_Choose DT)
{
    if(FORWARD == DT) { M_left_IN1 = 1; M_left_IN2 = 0; }
    else if(BACK == DT) { M_left_IN1 = 0; M_left_IN2 = 1; }
    else if(STOP == DT) { M_left_IN1 = 0; M_left_IN2 = 0; }
}

void Motor_Right_DIR(MotorDIR_Choose DT)
{
    if(FORWARD == DT) { M_right_IN3 = 1; M_right_IN4 = 0; }
    else if(BACK == DT) { M_right_IN3 = 0; M_right_IN4 = 1; }
    else if(STOP == DT) { M_right_IN3 = 0; M_right_IN4 = 0; }
}

void Load_Motor_PWM(int MOTOR1_PWM, int MOTOR2_PWM) 
{
    int pwm1_abs = abs(MOTOR1_PWM);
    int pwm2_abs = abs(MOTOR2_PWM);
    pwm1_abs = (pwm1_abs > PWM_MAX)? PWM_MAX : pwm1_abs;
    pwm2_abs = (pwm2_abs > PWM_MAX)? PWM_MAX : pwm2_abs;
    TIM_SetCompare1(TIM1, pwm1_abs);
    TIM_SetCompare4(TIM1, pwm2_abs);
}

void set_motor_enable(void)
{
    Flag.Is_EnMOTOR = 1;
    TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Enable);
}

void set_motor_disable(void)
{
    Flag.Is_EnMOTOR = 0;
    Motor_Left_DIR(STOP);
    Motor_Right_DIR(STOP);
    Load_Motor_PWM(0, 0);
    TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
    TIM_CCxCmd(TIM1, TIM_Channel_4, TIM_CCx_Disable);
}