#include "encoder.h" // 确保包含了encoder.h
#include "stm32f10x_gpio.h" // 包含GPIO库
#include "stm32f10x_rcc.h"  // 包含RCC库
#include "stm32f10x_tim.h"  // 包含TIM库

/**
 * 函数名：TIM2_Encoder_Init
 * 描述：定时器2编码设置
 * 输入：无
 * 输出：无
 */
void TIM2_Encoder_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef 			TIM_ICInitStructure;
	
	// 使能GPIO和TIM时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE); // 使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);  // 使能TIM2时钟
	
	// 配置编码器引脚为浮空输入
	GPIO_InitStructure.GPIO_Pin = ENCODER_TIM2_PINS; // 使用宏定义：GPIO_Pin_0 | GPIO_Pin_1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ENCODER_TIM2_GPIO_PORT,&GPIO_InitStructure); // 使用宏定义：GPIOA
	
	// 配置定时器时基
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 编码器模式通常使用向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65535; // 最大计数周期
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0; // 不分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; // 仅用于高级定时器
	TIM_TimeBaseInit(ENCODER_TIM2_TIMER,&TIM_TimeBaseInitStructure); // 使用宏定义：TIM2
	
	// 配置编码器接口模式
	TIM_EncoderInterfaceConfig(ENCODER_TIM2_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); // 使用宏定义：TIM2
	
	// 配置输入捕获滤波器
	TIM_ICInitStructure.TIM_ICFilter = 10; // 滤波器值，根据实际情况调整
	TIM_ICInit(ENCODER_TIM2_TIMER,&TIM_ICInitStructure); // 使用宏定义：TIM2
	
	// 使能更新中断 (可选，用于处理计数器溢出/下溢)
	TIM_ITConfig(ENCODER_TIM2_TIMER,TIM_IT_Update,ENABLE); // 使用宏定义：TIM2
	TIM_SetCounter(ENCODER_TIM2_TIMER,0); // 计数器清零
	
	// 启动定时器
	TIM_Cmd(ENCODER_TIM2_TIMER,ENABLE); // 使用宏定义：TIM2
}

/**
 * 函数名：TIM4_Encoder_Init
 * 描述：定时器4编码设置
 * 输入：无
 * 输出：无
 */
void TIM4_Encoder_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef 			TIM_ICInitStructure;
	
	// 使能GPIO和TIM时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE); // 使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // 使能TIM4时钟
	
	// 配置编码器引脚为浮空输入
	GPIO_InitStructure.GPIO_Pin = ENCODER_TIM4_PINS; // 使用宏定义：GPIO_Pin_6 | GPIO_Pin_7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ENCODER_TIM4_GPIO_PORT,&GPIO_InitStructure); // 使用宏定义：GPIOB
	
	// 配置定时器时基
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ENCODER_TIM4_TIMER,&TIM_TimeBaseInitStructure); // 使用宏定义：TIM4
	
	// 配置编码器接口模式
	TIM_EncoderInterfaceConfig(ENCODER_TIM4_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising); // 使用宏定义：TIM4
	
	// 配置输入捕获滤波器
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(ENCODER_TIM4_TIMER,&TIM_ICInitStructure); // 使用宏定义：TIM4
	
	// 使能更新中断
	TIM_ITConfig(ENCODER_TIM4_TIMER,TIM_IT_Update,ENABLE); // 使用宏定义：TIM4
	TIM_SetCounter(ENCODER_TIM4_TIMER,0);
	
	// 启动定时器
	TIM_Cmd(ENCODER_TIM4_TIMER,ENABLE); // 使用宏定义：TIM4
}

/**
 * 函数名：Read_Pulse
 * 描述：脉冲读取函数
 * 输入：Timx=(2,4)
 * 输出：对应定时器读取到的脉冲值
 */
int Read_Pulse(int Timx)
{
	int value;
	switch(Timx)
	{
		case 2:value =(short)TIM_GetCounter(ENCODER_TIM2_TIMER); TIM_SetCounter(ENCODER_TIM2_TIMER,0); break; // 使用宏定义
		case 4:value =(short)TIM_GetCounter(ENCODER_TIM4_TIMER); TIM_SetCounter(ENCODER_TIM4_TIMER,0);break; // 使用宏定义
		default:break;
	}
	return value;
}

/**
 * 函数名：TIM2_IRQHandler
 * 描述：定时器2中断服务函数
 * 输入：无
 * 输出：无
 */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER_TIM2_TIMER,TIM_IT_Update)== SET) // 使用宏定义
	{
		TIM_ClearITPendingBit(ENCODER_TIM2_TIMER,TIM_IT_Update); // 使用宏定义
	}
}

/**
 * 函数名：TIM4_IRQHandler
 * 描述：定时器4中断服务函数
 * 输入：无
 * 输出：无
 */
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(ENCODER_TIM4_TIMER,TIM_IT_Update)== SET) // 使用宏定义
	{
		TIM_ClearITPendingBit(ENCODER_TIM4_TIMER,TIM_IT_Update); // 使用宏定义
	}
}
