#ifndef __REDRAY_H
#define __REDRAY_H	 
#include "sys.h"
#include "delay.h"
#include "stm32f10x.h" //STM32头文件

#define REDRAY_PORT	GPIOA	//定义IO接口组
#define RED1		GPIO_Pin_2	//定义IO接口正面，有人为0，无人为1
#define RED2		GPIO_Pin_3	//定义IO接口


void opendoor(void);
void REDRAY_Init(void);//初始化

		 				    
#endif
