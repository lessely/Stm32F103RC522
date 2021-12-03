#include "REDRAY.h"
#include "delay.h"
#include "stm32f10x.h" //STM32头文件

void REDRAY_Init(void){ //触摸按键初始化
	GPIO_InitTypeDef  GPIO_InitStructure; //定义GPIO的初始化枚举结构	
    GPIO_InitStructure.GPIO_Pin = RED1 | RED2 ; //选择端口                       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //选择IO接口工作方式 //上拉电阻       
	GPIO_Init(REDRAY_PORT,&GPIO_InitStructure);			
}
 
void opendoor(void){
			u8 r1=1,r2=1;		
			u32 a=100;
			u32 b=100;
			TIM_SetCompare3(TIM3,1500);        
			TIM_SetCompare4(TIM3,6000);				//开闸		
			delay_ms(10);
		
		for(a=9999999;a>0;a--){
			r1=GPIO_ReadInputDataBit(REDRAY_PORT,RED1);
			if(r1==0){
				for(b=9999999;b>0;b--){
					r2=GPIO_ReadInputDataBit(REDRAY_PORT,RED2);
					if(r2==0){
						TIM_SetCompare3(TIM3,5000);        //关闸
						TIM_SetCompare4(TIM3,2300);	
						break;
										}}
				TIM_SetCompare3(TIM3,5000);        //关闸
				TIM_SetCompare4(TIM3,2300);
				break;
									}
//			r2=GPIO_ReadInputDataBit(REDRAY_PORT,RED2);
//			if(r2==0){
//				TIM_SetCompare3(TIM3,5000);        //关闸
//				TIM_SetCompare4(TIM3,2300);
//				break;
//									}
			
								}		
				TIM_SetCompare3(TIM3,5000);        //关闸
				TIM_SetCompare4(TIM3,2300);
							}
						
	
/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/



/*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
