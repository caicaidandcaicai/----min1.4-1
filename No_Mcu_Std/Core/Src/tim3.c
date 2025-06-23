#include "tim3.h"


/**
 * ��������Tim3_Init
 * ��������ʱ10ms
 * ���룺��
 * �������
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
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//��ʱ10ms
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	// ===================== ��TIM3 ���ȼ����á� =====================
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// ����һ���ϸߵ���ռ���ȼ������� 1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	// �����ȼ�������Ϊ0��1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	// ==============================================================
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}
