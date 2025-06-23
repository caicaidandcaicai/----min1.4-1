#include "key.h"
#include "delay.h"

// �����ⲿȫ�ֱ�������Щ������ main.c �ж���
extern uint8_t RoadLineCheck;
extern volatile uint8_t g_Task_Status_Changed_Flag;

/**
 * @brief  �����жϳ�ʼ������
 * @note   ���� PC13 Ϊ�ⲿ�ж����룬�½��ش���
 */
void KEY_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    EXTI_InitTypeDef   EXTI_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    // 1. ʹ��GPIOC��AFIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    // 2. ����PC13Ϊ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // 3. ����EXTI�ߵ�PC13
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);

    // 4. ����EXTI��
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 5. ����NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ���ȼ�����TIM3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  �ⲿ�ж�15~10�������
 */
void EXTI15_10_IRQHandler(void)
{
    // �ж��Ƿ���LINE13�������ж�
    if (EXTI_GetITStatus(EXTI_Line13)!= RESET)
    {
        Delay_ms(20); // �������
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)
        {
            // �л���������/ֹͣ��־
            RoadLineCheck =!RoadLineCheck;
            // ����״̬�����־��֪ͨ��ѭ������
            g_Task_Status_Changed_Flag = 1;
        }
        // ����жϱ�־λ
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
}