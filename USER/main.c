#include "stm32f10x.h" //STM32ͷ�ļ�
#include "usart.h"
#include "stm32f10x_spi.h"
#include "RC522.h"
#include "delay.h"
/******************************************************************************

Ӳ������
STM32F103C8T6       RC522ģ��
PA4��SPI1_NSS��      	SDA
PA5��SPI1_SCK��				SCK
PA6��SPI1_MISO��			MISO
PA7��SPI1_MOSI��			MOSI
PA11��RST��						RST
PB1��IRQ��						IRQ  δ����


USART1_TX   GPIOA.9
USART1_RX   GPIOA.10


******************************************************************************/

uint8_t Card_Type1[2];  
uint8_t Card_ID[4]; 
uint8_t Card_KEY[6] = {0xff,0xff,0xff,0xff,0xff,0xff};    //{0x11,0x11,0x11,0x11,0x11,0x11};   //����
uint8_t Card_Data[16];
uint8_t status;
uint8_t Identify_ID[4];
uint8_t MyCard_ID[4]={0xF9,0x1E,0x7C,0x14};//�ҵ����к�
uint8_t MyCard_Data[16]={0x0A,0x1B,0x2C,0x3D,0x4E,0x5F,0x0A,0x1B,0x2C,0x3D,0x4E,0x5F,0x0A,0x1B,0x2C,0x3D};

int main(void)
{
	uint8_t a;
	uint8_t c;
	Card_Type1[0]=0x04;
	Card_Type1[1]=0x00;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200	
 		
 	printf("\r\n********************System started successfully********************\r\n");
 
	delay_init();
	RC522_IO_Init();
	PcdReset();  //��λRC522
	PcdAntennaOff();  //�ر�����
	delay_ms(100);
	PcdAntennaOn();  //��������
	
	printf("\r\n***************************Working******************************\r\n");
	REDRAY_Init();
	TIM3_PWM_Init(59999,23);                       
	TIM_SetCompare3(TIM3,5000);        //�ı�Ƚ�ֵTIM3->CCR2�ﵽ����ռ�ձȵ�Ч��
	TIM_SetCompare4(TIM3,2300);					//��բ
	while(1)
	{
		delay_ms(500);
		if(MI_OK==PcdRequest(0x52, Card_Type1))  //Ѱ������������ɹ�����MI_OK  ��ӡ��ο���
//		if(MI_OK==PcdRequest(0x26, Card_Type1))  //Ѱ������������ɹ�����MI_OK   ��ӡ1�ο���
		{
			uint16_t cardType = (Card_Type1[0]<<8)|Card_Type1[1];//����ͬ��������
			printf("�����ͣ�(0x%04X)\r\n",cardType);  //"Card Type(0x%04X):"
			switch(cardType){
			case 0x4400:
					printf("Mifare UltraLight\r\n");
					break;
			case 0x0400:
					printf("Mifare One(S50)\r\n");
					break;
			case 0x0200:
					printf("Mifare One(S70)\r\n");
					break;
			case 0x0800:
					printf("Mifare Pro(X)\r\n");
					break;
			case 0x4403:
					printf("Mifare DESFire\r\n");
					break;
			default:
					printf("Unknown Card\r\n");
					break;
			}
			
			status = PcdAnticoll(Card_ID);//����ײ ����ɹ�����MI_OK
			if(status != MI_OK){
					printf("Anticoll Error\r\n");
			}else{
					printf("Serial Number:%02X%02X%02X%02X\r\n",Card_ID[0],Card_ID[1],Card_ID[2],Card_ID[3]);
			}
			
			status = PcdSelect(Card_ID);  //ѡ�� ����ɹ�����MI_OK
			if(status != MI_OK){
					printf("��Ƭ�ƶ��ٶ�̫�죬ѡ��ʧ��\r\n");
					printf("������ˢ��\r\n");
			}
			else{
				printf("ѡ���ɹ�\r\n");
					
			status = PcdAuthState(PICC_AUTHENT1A,5,Card_KEY,Card_ID);//��֤������ ����ɹ�����MI_OK
			if(status != MI_OK){
					printf("��������֤����\r\n");
			} 

			if(status == MI_OK){
			//ʶ�����к�
				a=0;						
				while(a<4&&Card_ID[a]==MyCard_ID[a]){
					a++;
				}
							if(a!=4){
						printf("��δע��\r\n");	
						printf("\r\n**********************************************************\r\n");
						break;				}			
							if(a==4){		
						printf("�����к���֤�ɹ�\r\n");		
						printf("���ڶ�ȡ����....\r\n");		
						status = PcdRead(5,Card_Data);                    //��һ�ΰ�����ȡ����16�ֽڵĿ�Ƭ���ݣ�ѡ����ַ�������ݣ��ɹ��򷵻�MI_OK
							delay_ms(500);
						if(status != MI_OK){
								printf("��ȡ����ʧ��\r\n");
								break;
						}else{
//							printf("����:\r\n");
//							for(c=0;c<16;c++){
//							printf("%02X ",Card_Data[c]);
//						}
							c=0;
						while(c<16&&Card_Data[c]==MyCard_Data[c])
							{c++;}										
						//printf("c��ֵ%d",c);
						}
					}
					
					//ʶ������
				if(c==16&&a==4)
				{printf("\r\n���к�������ʶ����ȷ\r\n");
					printf("���ڿ�բ\r\n");
					opendoor();
					printf("��բ�ɹ�\r\n");
				}
				if(c!=16&&a==4)
					printf("\r\n������֤ʧ��\r\n");
			}
		}
				status = PcdHalt();  //��Ƭ��������״̬		
				
 	printf("\r\n**********************************************************\r\n");
		}
	}
}



//			
//			memset(Card_ID,1,4);  //��������Ϊ�������ٿռ䣬�򽫱�������ֵΪһ��ֵ
//			memset(Card_Data,1,16);
//			Card_Data[0]=0xaa;
//			status = PcdWrite(5,Card_Data);                   //д��0XAA,0X01,0X01����ѡ����ַд�����ݣ��ɹ��򷵻�MI_OK
//			if(status != MI_OK){
//					printf("Card Write Error\r\n");
//					continue;
//			}
//			memset(Card_Data,0,16);  //����
//			delay_us(8);
//			
//			


//			memset(Card_Data,2,16);
//			Card_Data[0]=0xbb;
//			delay_us(8);
//			status = PcdWrite(5,Card_Data);                   //д��0Xbb,0X02,0X02����
//			if(status != MI_OK){
//					printf("Card Write Error\r\n");
//					continue;
//			}
//			delay_us(8);
//			
//			status = PcdRead(5,Card_Data);                    //��һ�ΰ�����ȡ����16�ֽڵĿ�Ƭ����
//			if(status != MI_OK){
//					printf("Card Read Error\r\n");
//					continue;
//			}else{
//				for(i=0;i<16;i++){
//					printf("%02X ",Card_Data[i]);
//				}
//				printf("\r\n");
//			}
			
			//memset(Card_Data,0,16);
		//	PcdHalt();  //��Ƭ��������״̬
			

//			if(status != MI_OK){
//					printf("PcdHalt Error\r\n");			
//			}
//			else
//			{
//					printf("PcdHalt OK\r\n");	
//			}
			
			
				
				