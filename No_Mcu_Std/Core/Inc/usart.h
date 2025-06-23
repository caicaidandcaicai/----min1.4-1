#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f10x.h" 
	  	
void uart_init(u32 bound);
void uart1_send_char(char ch);
void uart1_send_string(char* str);
#endif

