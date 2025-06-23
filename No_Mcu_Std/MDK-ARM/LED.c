#include "LED.h"


/**
 * 函数名：LED_Init
 * 描述：led模块对应的GPIO配置
 * 输入：无
 * 输出：无
 */

void LED_GPIO_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
void LED_RED_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}

void LED_GREEN_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED_YELLOW_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);	
}

void LED_RED_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}

void LED_GREEN_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED_YELLOW_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_11);	
}

