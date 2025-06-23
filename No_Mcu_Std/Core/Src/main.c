#include "stm32f10x.h"
#include "usart.h"
#include "No_Mcu_Ganv_Grayscale_Sensor_Config.h"
#include "gpio.h"
#include "delay.h"
#include "Motor.h"
#include "tim3.h"
#include "MyConfig.h"
#include "Tim1.h"
#include "key.h"
#include "encoder.h"
#include "Infrared.h"
#include <stdio.h>
#include <string.h>

unsigned char rx_buff[256] = {0}; // 必须是数组
uint8_t RoadLineCheck = 0; // 使用单个变量即可
volatile uint8_t g_Task_Status_Changed_Flag = 0;

extern No_MCU_Sensor GrayscaleSensor;

int main(void)
{
    NVIC_Config();
    uart_init(115200);
    Delay_Init();
    gpio_init();
    Motor_GPIO_Init();
    adc_init();
    TIM1_PWM_Init(0, 7199); // 周期为 2000
    TIM2_Encoder_Init();
    TIM4_Encoder_Init();
    Tim3_Init();
    KEY_Init();
    Infrafred_GPIO_Init();
    
    uart1_send_string((char*)"Velocity PID Test Ready.\r\n");
    Delay_ms(500);

    for(;;)
    {
        if (g_Task_Status_Changed_Flag == 1)
        {
            g_Task_Status_Changed_Flag = 0;
            if (RoadLineCheck == 1)
            {
                uart1_send_string("Test Started!\r\n");
                Velocity_Test_Start();
            }
            else
            {
                uart1_send_string("Test Stopped.\r\n");
                Velocity_Test_Stop();
            }
        }

        if (Flag.Start_Line == 1)
        {
            sprintf((char *)rx_buff, 
                    "T_Spd:%.1f, A_Spd:%.1f, V_Out:%d, Dist:%.1f\r\n",
                    g_Target_Speed_Debug,
                    g_Actual_Speed_Debug,
                    g_Velocity_Out_Debug,
                    g_Distance_Debug);
            uart1_send_string((char *)rx_buff);
            memset(rx_buff, 0, 256);
        }
        
        Delay_ms(100);
    }
}