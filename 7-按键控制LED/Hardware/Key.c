#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	//����ʼ��Ϊ���������ģʽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Key;
	
	GPIO_Init_Key.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Key.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_Init_Key.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_Init_Key);
	//****************************
	

}
	//��ȡ��������ĺ���
uint8_t Key_GetNum(void)
{
	//�õ���ȡGPIO�˿ڵĹ���
	
	
	uint8_t Key_Num = 0;
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1 ) == 0)
	{
		Delay_ms(20);//��������
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);//���º�û�����ֽ��Ῠ������
		Delay_ms(20);//��������ʱ�Ķ���
		Key_Num = 1;
	}
	
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(20);//��������
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);//���º�û�����ֽ��Ῠ������
		Delay_ms(20);//��������ʱ�Ķ���
		Key_Num = 2;
	}
	return Key_Num;
}













