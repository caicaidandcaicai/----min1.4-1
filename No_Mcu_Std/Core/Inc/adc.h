#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h" // ����STM32F10x��׼�����ͷ�ļ�

// --- ADC ���������ź궨�� ---
// ��Щ�궨����ADC���������ӵ�GPIO�˿ڡ����š���Ӧ��ADCͨ���Լ�GPIO�˿ڵ�ʱ��ʹ�ܺꡣ
// �����Ҫ�޸�ADC���ţ�ֻ���޸����º궨�弴�ɡ�

// ����ADC���������ӵ�GPIO�˿� (���磺GPIOA, GPIOB, etc.)
#define ADC_SENSOR_GPIO_PORT    GPIOA

// ����ADC���������ӵ�GPIO���� (���磺GPIO_Pin_0, GPIO_Pin_3, etc.)
#define ADC_SENSOR_GPIO_PIN     GPIO_Pin_3

// ����ADC��������Ӧ��ADCͨ�� (���磺ADC_Channel_0, ADC_Channel_3, etc.)
// ע�⣺���ͨ���ű�����GPIO_PIN��Ӧ��
// PA0 -> ADC_Channel_0
// PA1 -> ADC_Channel_1
// PA2 -> ADC_Channel_2
// PA3 -> ADC_Channel_3
// ...
// PB0 -> ADC_Channel_8
// PB1 -> ADC_Channel_9
#define ADC_SENSOR_ADC_CHANNEL  ADC_Channel_3

// ����ADC������GPIO�˿ڵ�ʱ��ʹ�ܺ� (���磺RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, etc.)
// ������ADC_SENSOR_GPIO_PORTƥ�䡣
#define ADC_SENSOR_GPIO_CLK     RCC_APB2Periph_GPIOA
// ---------------------------


// ADCģ���ʼ����������
// ���ܣ���ʼ��ADC1��������ADC_SENSOR_GPIO_PINΪģ�����롣
void adc_init(void);

// ��ȡADCת��ֵ��������
// ���ܣ�����һ��ADCת�����ȴ�ת����ɣ�������12λ��ת�������
// ����ֵ��0-4095 ֮���ADCԭʼֵ��
unsigned short adc_getValue(void);

#endif /* __ADC_H */
