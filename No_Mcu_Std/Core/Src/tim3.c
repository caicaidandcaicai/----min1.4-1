#include "tim3.h"


/**
 * 函数名：Tim3_Init
 * 描述：定时10ms
 * 输入：无
 * 输出：无
 */

void Tim3_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//计时10ms
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	// ===================== 【TIM3 优先级配置】 =====================
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// 设置一个较高的抢占优先级，例如 1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	// 子优先级可以设为0或1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	// ==============================================================
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}
