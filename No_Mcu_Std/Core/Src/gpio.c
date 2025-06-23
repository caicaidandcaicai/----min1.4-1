#include "gpio.h"
void gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOB,GPIO_Pin_0|GPIO_Pin_1,Bit_RESET);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,Bit_RESET);
}

