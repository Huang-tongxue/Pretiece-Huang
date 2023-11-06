#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	//**���ó�ʼ��ʱ������
	//*����GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//*����AFIO�����ʼ������Ҳ�����GPIOͷ�ļ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	//**����GOIP
	//*����ṹ��
	GPIO_InitTypeDef GPIO_InitStruct;
	//*����ѡ��14�ſ�
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	//*���������ģʽӦ�ò�ѯ�ĵ�������Ҫ�������������
	//*�������룬�������룬�������붼���ԣ�����ѡ����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*����GPIOInit����
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	
	//**����AFIO����
	//*EXTI�ⲿ����ѡ��
	//*ѡ��B��14��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	//** ����EXTI
	//*���ĸ����Ƕ�״̬�Ĵ����Ķ�ȡ
	//*FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
	//*void EXTI_ClearFlag(uint32_t EXTI_Line);
	//*�����������ж��Ƿ������������ж�
	//*ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
	//*void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
	EXTI_InitTypeDef EXTI_InitStruct;
	//*����һ���ṹ��
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*�����ص�ѡ���������ػ����½��أ�����˫����
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//*�ṹ���ʼ��
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**����NVIC
	//*��ΪNVIC���ں����裬����������������
	//*misc. h
	//*�жϷ���
	//*void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
	//*void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
	//*�����ж�������
	//*void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
	//*void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
	//*void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
	
	//*���ȼ�����
	//*���鷽ʽ��������ֻ��ʹ��һ�֣�ִ��һ�ξͿ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC�ṹ�嶨��
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
}


uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}
//**�жϺ���
void EXTI15_10_IRQHandler(void)//������Դ�������ļ�
{
	//**�����жϱ�־λ���ж�
	//*10��15���ܽ���������Ҫ�ж��ǲ���������ź�Դ����
	if(EXTI_GetITStatus( EXTI_Line14) == SET)
	{
//		/*��������������������󣬿��ٴ��ж����ŵ�ƽ���Ա��ⶶ��*/
//		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
//		{
//			CountSensor_Count ++;
//		}
		CountSensor_Count ++;
		//*����жϱ�־λ
		EXTI_ClearITPendingBit( EXTI_Line14);
	}
	
}