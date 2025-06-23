#include "encoder.h" // ȷ��������encoder.h
#include "stm32f10x_gpio.h" // ����GPIO��
#include "stm32f10x_rcc.h"  // ����RCC��
#include "stm32f10x_tim.h"  // ����TIM��

/**
 * ��������TIM2_Encoder_Init
 * ��������ʱ��2��������
 * ���룺��
 * �������
 */
void TIM2_Encoder_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef 			TIM_ICInitStructure;
	
	// ʹ��GPIO��TIMʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE); // ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);  // ʹ��TIM2ʱ��
	
	// ���ñ���������Ϊ��������
	GPIO_InitStructure.GPIO_Pin = ENCODER_TIM2_PINS; // ʹ�ú궨�壺GPIO_Pin_0 | GPIO_Pin_1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ENCODER_TIM2_GPIO_PORT,&GPIO_InitStructure); // ʹ�ú궨�壺GPIOA
	
	// ���ö�ʱ��ʱ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ������ģʽͨ��ʹ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 65535; // ����������
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0; // ����Ƶ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // �����ڸ߼���ʱ��
	TIM_TimeBaseInit(ENCODER_TIM2_TIMER,&TIM_TimeBaseInitStructure); // ʹ�ú궨�壺TIM2
	
	// ���ñ������ӿ�ģʽ
	TIM_EncoderInterfaceConfig(ENCODER_TIM2_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); // ʹ�ú궨�壺TIM2
	
	// �������벶���˲���
	TIM_ICInitStructure.TIM_ICFilter = 10; // �˲���ֵ������ʵ���������
	TIM_ICInit(ENCODER_TIM2_TIMER,&TIM_ICInitStructure); // ʹ�ú궨�壺TIM2
	
	// ʹ�ܸ����ж� (��ѡ�����ڴ�����������/����)
	TIM_ITConfig(ENCODER_TIM2_TIMER,TIM_IT_Update,ENABLE); // ʹ�ú궨�壺TIM2
	TIM_SetCounter(ENCODER_TIM2_TIMER,0); // ����������
	
	// ������ʱ��
	TIM_Cmd(ENCODER_TIM2_TIMER,ENABLE); // ʹ�ú궨�壺TIM2
}

/**
 * ��������TIM4_Encoder_Init
 * ��������ʱ��4��������
 * ���룺��
 * �������
 */
void TIM4_Encoder_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef 			TIM_ICInitStructure;
	
	// ʹ��GPIO��TIMʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE); // ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // ʹ��TIM4ʱ��
	
	// ���ñ���������Ϊ��������
	GPIO_InitStructure.GPIO_Pin = ENCODER_TIM4_PINS; // ʹ�ú궨�壺GPIO_Pin_6 | GPIO_Pin_7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ENCODER_TIM4_GPIO_PORT,&GPIO_InitStructure); // ʹ�ú궨�壺GPIOB
	
	// ���ö�ʱ��ʱ��
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ENCODER_TIM4_TIMER,&TIM_TimeBaseInitStructure); // ʹ�ú궨�壺TIM4
	
	// ���ñ������ӿ�ģʽ
	TIM_EncoderInterfaceConfig(ENCODER_TIM4_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); // ʹ�ú궨�壺TIM4
	
	// �������벶���˲���
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(ENCODER_TIM4_TIMER,&TIM_ICInitStructure); // ʹ�ú궨�壺TIM4
	
	// ʹ�ܸ����ж�
	TIM_ITConfig(ENCODER_TIM4_TIMER,TIM_IT_Update,ENABLE); // ʹ�ú궨�壺TIM4
	TIM_SetCounter(ENCODER_TIM4_TIMER,0);
	
	// ������ʱ��
	TIM_Cmd(ENCODER_TIM4_TIMER,ENABLE); // ʹ�ú궨�壺TIM4
}

/**
 * ��������Read_Pulse
 * �����������ȡ����
 * ���룺Timx=(2,4)
 * �������Ӧ��ʱ����ȡ��������ֵ
 */
int Read_Pulse(int Timx)
{
	int value;
	switch(Timx)
	{
		case 2:value =(short)TIM_GetCounter(ENCODER_TIM2_TIMER); TIM_SetCounter(ENCODER_TIM2_TIMER,0); break; // ʹ�ú궨��
		case 4:value =(short)TIM_GetCounter(ENCODER_TIM4_TIMER); TIM_SetCounter(ENCODER_TIM4_TIMER,0);break; // ʹ�ú궨��
		default:break;
	}
	return value;
}

/**
 * ��������TIM2_IRQHandler
 * ��������ʱ��2�жϷ�����
 * ���룺��
 * �������
 */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER_TIM2_TIMER,TIM_IT_Update)== SET) // ʹ�ú궨��
	{
		TIM_ClearITPendingBit(ENCODER_TIM2_TIMER,TIM_IT_Update); // ʹ�ú궨��
	}
}

/**
 * ��������TIM4_IRQHandler
 * ��������ʱ��4�жϷ�����
 * ���룺��
 * �������
 */
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER_TIM4_TIMER,TIM_IT_Update)== SET) // ʹ�ú궨��
	{
		TIM_ClearITPendingBit(ENCODER_TIM4_TIMER,TIM_IT_Update); // ʹ�ú궨��
	}
}
