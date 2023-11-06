#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"

uint8_t Key_Num;//����һ��ȫ�ֱ��������ڴ�ŷ���ֵ
uint8_t Menu = 0;
uint8_t OLED_TheMenu[4] = {1, 2, 3, 4};//��Ž���

int main(void)
{
	Key_Init();
	OLED_Init();
	//*******************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��ʼ��ʱ��
	
	GPIO_InitTypeDef GPIO_InitStructure;//����һ���ṹ��������2
	//��ʼ���ṹ���Ա
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//ֱ��ȫ�����ų�ʼ��Ϊ�������ģʽGPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	//****************

	while (1)
	{
		if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1 ) == 0)
		{
			Delay_ms(20);//��������
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);//���º�û�����ֽ��Ῠ������
			Delay_ms(20);//��������ʱ�Ķ���
			Menu++;
			if(Menu == 4)
				Menu = 0;
			OLED_ShowMenu();
		}
		
		if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
		{
			Delay_ms(20);//��������
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);//���º�û�����ֽ��Ῠ������
			Delay_ms(20);//��������ʱ�Ķ���
			
			if(Menu != 0)
				Menu--;
			else
				Menu = 3;
			OLED_ShowMenu();
		}

	}
	
}
