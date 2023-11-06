#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��ʼ��ʱ��
	
	GPIO_InitTypeDef GPIO_InitStructure;//����һ���ṹ��������2
	//��ʼ���ṹ���Ա
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	
	while (1)
	{
		for(int i = 0;i < 3; i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);
		Delay_ms(100);
		}
		
		for(int i = 0;i < 3; i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
		Delay_ms(400);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);
		Delay_ms(400);
		}
		
		for(int i = 0;i < 3; i++)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_RESET);
		Delay_ms(100);
		}
		GPIO_WriteBit(GPIOA, GPIO_Pin_0,Bit_SET);
		Delay_ms(1000);

	}
	
}
