#ifndef __REDRAY_H
#define __REDRAY_H	 
#include "sys.h"
#include "delay.h"
#include "stm32f10x.h" //STM32ͷ�ļ�

#define REDRAY_PORT	GPIOA	//����IO�ӿ���
#define RED1		GPIO_Pin_2	//����IO�ӿ����棬����Ϊ0������Ϊ1
#define RED2		GPIO_Pin_3	//����IO�ӿ�


void opendoor(void);
void REDRAY_Init(void);//��ʼ��

		 				    
#endif
