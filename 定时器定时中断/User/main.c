#include "stm32f10x.h"                  // Device header
#include "Alarm.h"

uint16_t num = 0;
uint8_t Key_Num;

int main(void)
{
	Alarm_Init();
	
	while(1)
	{
		OLED_ShowString(1,1,"Settting Time:");
		OLED_ShowNum(2,1,num,5);
		num += Get_Encoder_Count();
	}
}		



//	Timer_Init();
//	OLED_Init();
//	//*******************
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��ʼ��ʱ��
//	
//	GPIO_InitTypeDef GPIO_InitStructure;//����һ���ṹ��������2
//	//��ʼ���ṹ���Ա
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//ֱ��ȫ�����ų�ʼ��Ϊ�������ģʽGPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
//	
//	OLED_ShowString(1,1,"Num:");
//	while(1)
//	{
//		OLED_ShowNum(1,5,NUM,5);
//		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
//	}
	
