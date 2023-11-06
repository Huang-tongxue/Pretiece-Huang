#include "stm32f10x.h"                  // Device header
#include "Delay.h"
extern uint8_t Key_Num;

void Key_Init(void)
{
	//**���ó�ʼ��ʱ������
	//*����GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//**����GOIP
	//*����ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*����GPIOInit����
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	//**����AFIO����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	//** ����EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	//*����һ���ṹ��
	EXTI_InitStruct.EXTI_Line = EXTI_Line2 | EXTI_Line3;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*�����ص�ѡ���������ػ����½��أ�����˫����
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	//*�ṹ���ʼ��
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**����NVIC
	//*���ȼ�����
	//*���鷽ʽ��������ֻ��ʹ��һ�֣�ִ��һ�ξͿ�����
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC�ṹ�嶨��
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
}


//void Key_Init(void)
//{
//	//����ʼ��Ϊ���������ģʽ
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	
//	GPIO_InitTypeDef GPIO_Init_Key;
//	
//	GPIO_Init_Key.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init_Key.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
//	GPIO_Init_Key.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA, &GPIO_Init_Key);
//	//****************************
//	

//}
	//��ȡ��������ĺ���
//uint8_t Key_GetNum(void)
//{
//	//�õ���ȡGPIO�˿ڵĹ���
//	
//	
//	uint8_t Key_Num = 0;
//	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1 ) == 0)
//	{
//		Delay_ms(20);//��������
//		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);//���º�û�����ֽ��Ῠ������
//		Delay_ms(20);//��������ʱ�Ķ���
//		Key_Num = 1;
//	}
//	
//	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
//	{
//		Delay_ms(20);//��������
//		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);//���º�û�����ֽ��Ῠ������
//		Delay_ms(20);//��������ʱ�Ķ���
//		Key_Num = 2;
//	}
//	return Key_Num;
//}



uint8_t EXTI2_IRQHandler(void)
{
	//�õ���ȡGPIO�˿ڵĹ���
	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2 ) == 0)
	{
		Delay_ms(20);//��������
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0);//���º�û�����ֽ��Ῠ������
		Delay_ms(20);//��������ʱ�Ķ���
		Key_Num = 2;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
	return Key_Num;
}

uint8_t EXTI3_IRQHandler(void)
{
	//�õ���ȡGPIO�˿ڵĹ���
	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3 ) == 0)
	{
		Delay_ms(20);//��������
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0);//���º�û�����ֽ��Ῠ������
		Delay_ms(20);//��������ʱ�Ķ���
		Key_Num = 3;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
	return Key_Num;
}








