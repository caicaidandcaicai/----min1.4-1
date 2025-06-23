#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h" // 包含STM32F10x标准外设库头文件

// --- ADC 传感器引脚宏定义 ---
// 这些宏定义了ADC传感器连接的GPIO端口、引脚、对应的ADC通道以及GPIO端口的时钟使能宏。
// 如果需要修改ADC引脚，只需修改以下宏定义即可。

// 定义ADC传感器连接的GPIO端口 (例如：GPIOA, GPIOB, etc.)
#define ADC_SENSOR_GPIO_PORT    GPIOA

// 定义ADC传感器连接的GPIO引脚 (例如：GPIO_Pin_0, GPIO_Pin_3, etc.)
#define ADC_SENSOR_GPIO_PIN     GPIO_Pin_3

// 定义ADC传感器对应的ADC通道 (例如：ADC_Channel_0, ADC_Channel_3, etc.)
// 注意：这个通道号必须与GPIO_PIN对应。
// PA0 -> ADC_Channel_0
// PA1 -> ADC_Channel_1
// PA2 -> ADC_Channel_2
// PA3 -> ADC_Channel_3
// ...
// PB0 -> ADC_Channel_8
// PB1 -> ADC_Channel_9
#define ADC_SENSOR_ADC_CHANNEL  ADC_Channel_3

// 定义ADC传感器GPIO端口的时钟使能宏 (例如：RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB, etc.)
// 必须与ADC_SENSOR_GPIO_PORT匹配。
#define ADC_SENSOR_GPIO_CLK     RCC_APB2Periph_GPIOA
// ---------------------------


// ADC模块初始化函数声明
// 功能：初始化ADC1，并配置ADC_SENSOR_GPIO_PIN为模拟输入。
void adc_init(void);

// 获取ADC转换值函数声明
// 功能：启动一次ADC转换，等待转换完成，并返回12位的转换结果。
// 返回值：0-4095 之间的ADC原始值。
unsigned short adc_getValue(void);

#endif /* __ADC_H */
