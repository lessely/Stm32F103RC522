#include "REDRAY.h"
#include "delay.h"
#include "stm32f10x.h" //STM32ͷ�ļ�

void REDRAY_Init(void){ //����������ʼ��
	GPIO_InitTypeDef  GPIO_InitStructure; //����GPIO�ĳ�ʼ��ö�ٽṹ	
    GPIO_InitStructure.GPIO_Pin = RED1 | RED2 ; //ѡ��˿�                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ѡ��IO�ӿڹ�����ʽ //��������       
	GPIO_Init(REDRAY_PORT,&GPIO_InitStructure);			
}
 
void opendoor(void){
			u8 r1=1,r2=1;		
			u32 a=100;
			u32 b=100;
			TIM_SetCompare3(TIM3,1500);        
			TIM_SetCompare4(TIM3,6000);				//��բ		
			delay_ms(10);
		
		for(a=9999999;a>0;a--){
			r1=GPIO_ReadInputDataBit(REDRAY_PORT,RED1);
			if(r1==0){
				for(b=9999999;b>0;b--){
					r2=GPIO_ReadInputDataBit(REDRAY_PORT,RED2);
					if(r2==0){
						TIM_SetCompare3(TIM3,5000);        //��բ
						TIM_SetCompare4(TIM3,2300);	
						break;
										}}
				TIM_SetCompare3(TIM3,5000);        //��բ
				TIM_SetCompare4(TIM3,2300);
				break;
									}
//			r2=GPIO_ReadInputDataBit(REDRAY_PORT,RED2);
//			if(r2==0){
//				TIM_SetCompare3(TIM3,5000);        //��բ
//				TIM_SetCompare4(TIM3,2300);
//				break;
//									}
			
								}		
				TIM_SetCompare3(TIM3,5000);        //��բ
				TIM_SetCompare4(TIM3,2300);
							}
						
	
/*********************************************************************************************
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/



/*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
