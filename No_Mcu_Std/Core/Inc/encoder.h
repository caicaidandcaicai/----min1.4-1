#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h" // 包含STM32F10x标准外设库头文件

// --- TIM2 编码器引脚定义 (PA0, PA1) ---
#define ENCODER_TIM2_GPIO_PORT      GPIOA
#define ENCODER_TIM2_PIN_A          GPIO_Pin_0
#define ENCODER_TIM2_PIN_B          GPIO_Pin_1
#define ENCODER_TIM2_PINS           (ENCODER_TIM2_PIN_A | ENCODER_TIM2_PIN_B)
#define ENCODER_TIM2_TIMER          TIM2

// --- TIM4 编码器引脚定义 (PB6, PB7) ---
#define ENCODER_TIM4_GPIO_PORT      GPIOB
#define ENCODER_TIM4_PIN_A          GPIO_Pin_6
#define ENCODER_TIM4_PIN_B          GPIO_Pin_7
#define ENCODER_TIM4_PINS           (ENCODER_TIM4_PIN_A | ENCODER_TIM4_PIN_B)
#define ENCODER_TIM4_TIMER          TIM4

// 函数声明
void TIM2_Encoder_Init(void);
void TIM4_Encoder_Init(void);
int Read_Pulse(int Timx);

#endif /* __ENCODER_H */
