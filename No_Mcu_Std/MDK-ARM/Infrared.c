#include "Infrared.h"
#include "Delay.h"
/**
 * ��������Infrafred_Init
 * ���������⴫������Ӧ��GPIO����
 * ���룺��
 * �������
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
 * ��������LoadOrNot(void)
 * ���������ҩƷװ��
 * ���룺��
 * �����0-�ȴ�ҩƷ 1-װҩ 2-ȡҩ���
 */

uint8_t LoadOrNot(void)
{
	static uint8_t load_flag;
//	
//	if(DRUG_Testing == 1)//��ʾװ��ҩƷ���
//	{
//		load_flag = 1;
//		return 1 ;
//	}
//	else if(DRUG_Testing == 0)
//	{
//		if(load_flag == 1)//ȡҩ���
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
