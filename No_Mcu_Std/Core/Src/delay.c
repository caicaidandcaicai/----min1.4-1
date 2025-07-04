#include  "delay.h"
 
uint8_t fac_us=0;
uint16_t fac_ms=0;
 
void Delay_Init()
{
	//只可以选择不分频或者8分频，这里选择系统时钟8分频，最后频率为9MHZ
	SysTick->CTRL &= ~(1<<2);
	//SystemCoreClock为72000000，最终fac_us为9，也就是记录震动9次。因为频率为9MHZ所以为1us
	fac_us  = SystemCoreClock  / 8000000;  
	fac_ms  = fac_us*1000;  //1000us=1ms
}
 
/*
	CTRL     SysTick控制及状态寄存器
	LOAD     SysTick重装载数值寄存器
	VAL      SysTick当前数值寄存器
*/
void Delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD  =nus*fac_us;   //设置加载的值，比如1us就要计数9次。nus传入1，CALIB=1*9=9，最后就是1us
	SysTick->VAL   =0x00;         //清空计数器中的值，LOAD里的值不是写入后就会加载，而是在systick使能且VAL值为0时才加载
	SysTick->CTRL  |=SysTick_CTRL_ENABLE_Msk;  //使能时钟，开始计时
	do
	{
		temp=SysTick->CTRL;   //查询是否计数完成
	}while((temp&0x01)&&!(temp&(1<<16)));   //先判断定时器是否在运行，再判断是否计数完成
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}
 
void Delay_ms(uint32_t nms)
{
	uint32_t temp;
	SysTick->LOAD  =nms*fac_ms;   //设置加载的值，比如1us就要计数9次。nus传入1，CALIB=1*9=9，最后就是1us
	SysTick->VAL   =0x00;         //清空计数器中的值，LOAD里的值不是写入后就会加载，而是在systick使能且VAL值为0时才加载
	SysTick->CTRL  |=SysTick_CTRL_ENABLE_Msk;  //使能时钟，开始计时
	do
	{
		temp=SysTick->CTRL;   //查询是否计数完成
	}while((temp&0x01)&&!(temp&(1<<16)));   //先判断定时器是否在运行，再判断是否计数完成
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}


