#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体填充参数2
	//初始化结构体成员
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	
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
