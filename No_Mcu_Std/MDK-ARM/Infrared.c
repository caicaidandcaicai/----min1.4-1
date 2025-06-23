#include "Infrared.h"
#include "Delay.h"
/**
 * 函数名：Infrafred_Init
 * 描述：红外传感器对应的GPIO配置
 * 输入：无
 * 输出：无
 */
 
void Infrafred_GPIO_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/**
 * 函数名：LoadOrNot(void)
 * 描述：检测药品装载
 * 输入：无
 * 输出：0-等待药品 1-装药 2-取药完成
 */

uint8_t LoadOrNot(void)
{
	static uint8_t load_flag;
//	
//	if(DRUG_Testing == 1)//表示装载药品完成
//	{
//		load_flag = 1;
//		return 1 ;
//	}
//	else if(DRUG_Testing == 0)
//	{
//		if(load_flag == 1)//取药完成
//		{
//			return 2 ;
//		}
//	}
//	return 0 ;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==1)
	{
		if(load_flag==1)
		{
			Delay_ms(100);
			return 2;
		}
	}	
	else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0)
	{
		load_flag = 1;
		Delay_us(100);
		return 0 ;
	}
return 1;
}
