#include "adc.h" // 假设这个头文件包含了必要的STM32库函数声明

// --- ADC 传感器引脚宏定义 ---
// 定义ADC传感器连接的GPIO端口
#define ADC_SENSOR_GPIO_PORT    GPIOA
// 定义ADC传感器连接的GPIO引脚
#define ADC_SENSOR_GPIO_PIN     GPIO_Pin_3
// 定义ADC传感器对应的ADC通道
#define ADC_SENSOR_ADC_CHANNEL  ADC_Channel_3
// 定义ADC传感器GPIO端口的时钟使能宏
// 注意：如果ADC_SENSOR_GPIO_PORT改为GPIOB，这里也要相应改为RCC_APB2Periph_GPIOB
#define ADC_SENSOR_GPIO_CLK     RCC_APB2Periph_GPIOA
// ---------------------------

void adc_init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	// 1. 使能GPIO端口和ADC1时钟
	// 使用宏定义来使能对应GPIO端口的时钟
	RCC_APB2PeriphClockCmd(ADC_SENSOR_GPIO_CLK | RCC_APB2Periph_ADC1, ENABLE);
	// 设置ADC分频因子为4 (PCLK2 / 4 = 72MHz / 4 = 18MHz)
	// 建议根据实际情况调整，如PCLK2_Div6或PCLK2_Div8，使ADC时钟在14MHz以内更稳定
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);

	// 2. 配置ADC传感器引脚为模拟输入
	GPIO_InitStructure.GPIO_Pin = ADC_SENSOR_GPIO_PIN; // 使用宏定义
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入模式
	GPIO_Init(ADC_SENSOR_GPIO_PORT, &GPIO_InitStructure); // 使用宏定义

	// 3. ADC1初始化配置
	ADC_DeInit(ADC1); // 复位ADC1
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1; // 规则转换通道数目
	ADC_Init(ADC1, &ADC_InitStructure);

	// 4. 使能ADC1并进行校准
	ADC_Cmd(ADC1, ENABLE); // 使能ADC1
	ADC_ResetCalibration(ADC1); // 复位校准
	while (ADC_GetResetCalibrationStatus(ADC1)); // 等待复位校准结束
	ADC_StartCalibration(ADC1); // 开启校准
	while (ADC_GetCalibrationStatus(ADC1)); // 等待校准结束
}

unsigned short adc_getValue()
{
	// 1. 配置ADC通道为ADC_SENSOR_ADC_CHANNEL
	ADC_RegularChannelConfig(ADC1, ADC_SENSOR_ADC_CHANNEL, 1, ADC_SampleTime_239Cycles5); // 使用宏定义

	// 2. 启动转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	// 3. 等待转换结束标志
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); // EOC: End Of Conversion

	// 4. 返回转换结果
	return ADC_GetConversionValue(ADC1);
}
