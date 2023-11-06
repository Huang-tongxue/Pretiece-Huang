#include "stm32f10x.h"                  // Device header
extern uint16_t NUM;//extern��������ʹ�ÿ��Կ�ԽC�ļ�ʹ�ñ���

void Timer_Init(void)//��ʼ����ʱ��  
{
	//��һ������ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//ѡ��Ϊ�ڲ�ʱ��
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00F);//ETR���ŵ��ⲿʱ��ģʽ2����
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStruct;
	TIM_TimBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1; 
	TIM_TimBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStruct.TIM_Period = 10 - 1;//��ҪС��65535
	TIM_TimBaseInitStruct.TIM_Prescaler = 1 - 1;//��ҪС��65535
	TIM_TimBaseInitStruct.TIM_RepetitionCounter = 0;

	
	TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStruct);TIM_ClearFlag(TIM2, TIM_FLAG_Update);//�ֶ������жϱ�־λ���
	//ʱ����Ԫ�������
	//ʹ�ܸ����ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//�����˸����жϵ�NVIC��ͨ·
	//NVIC
	//���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ������
	NVIC_InitTypeDef NVIC_InitTypeDefStructer;
	NVIC_InitTypeDefStructer.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTypeDefStructer.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDefStructer.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�
	NVIC_InitTypeDefStructer.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitTypeDefStructer);
	//�ж�ͨ����ͨ
	//���һ����������ʱ��
	TIM_Cmd(TIM12,ENABLE);
	
	
	
}


//�жϺ���
void TIM2_IQRHandler(void)
{
	//����жϱ�־λ
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		NUM++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//�����־λ
	}
	
	
}


uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}