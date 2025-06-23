#include "key.h"
#include "delay.h"

// 声明外部全局变量，这些变量在 main.c 中定义
extern uint8_t RoadLineCheck;
extern volatile uint8_t g_Task_Status_Changed_Flag;

/**
 * @brief  按键中断初始化函数
 * @note   配置 PC13 为外部中断输入，下降沿触发
 */
void KEY_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    // 1. 使能GPIOC和AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    // 2. 配置PC13为上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // 3. 连接EXTI线到PC13
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

    // 4. 配置EXTI线
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 5. 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 优先级低于TIM3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  外部中断15~10服务程序
 */
void EXTI15_10_IRQHandler(void)
{
    // 判断是否是LINE13触发的中断
    if (EXTI_GetITStatus(EXTI_Line13)!= RESET)
    {
        Delay_ms(20); // 软件消抖
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)
        {
            // 切换任务启动/停止标志
            RoadLineCheck =!RoadLineCheck;
            // 设置状态变更标志，通知主循环处理
            g_Task_Status_Changed_Flag = 1;
        }
        // 清除中断标志位
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
}