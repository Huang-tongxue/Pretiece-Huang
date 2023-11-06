#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;



void Encoder_Init(void)
{
	//**���ó�ʼ��ʱ������
	//*����GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//**����GOIP
	//*����ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*����GPIOInit����
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//**����AFIO����
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	//** ����EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	//*����һ���ṹ��
	EXTI_InitStruct.EXTI_Line = EXTI_Line1 | EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*�����ص�ѡ���������ػ����½��أ�����˫����
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//*�ṹ���ʼ��
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**����NVIC
	//*���ȼ�����
	//*���鷽ʽ��������ֻ��ʹ��һ�֣�ִ��һ�ξͿ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC�ṹ�嶨��
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
}

int16_t Get_Encoder_Count(void)
{
	uint16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;//����һ���仯��ֵ
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		/*��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
			{
				Encoder_Count --;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		/*��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
			{
				Encoder_Count ++;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

//�жϺ���1��Ҫdely   2��Ҫ���ú���������ͬ��Ӳ��
