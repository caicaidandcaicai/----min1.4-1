#ifndef __INFRARED_H
#define __INFRARED_H


#include "stm32f10x.h"
#include "sys.h"

#define DRUG_Testing   PAin(12)

void Infrafred_GPIO_Init(void);
uint8_t LoadOrNot(void);

#endif
