#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "sys.h"

void LED_GPIO_Init(void);
#define LED_RED     PBout(3)
#define LED_GREEN   PBout(4)
#define LED_YELLOW  PBout(5)

void LED_RED_ON(void);
void LED_GREEN_ON(void);
void LED_YELLOW_ON(void);

void LED_RED_OFF(void);
void LED_GREEN_OFF(void);
void LED_YELLOW_OFF(void);
#endif
