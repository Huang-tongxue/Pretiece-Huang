#include "stm32f10x.h"                  // Device header
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//
	
	//********************************************
	GPIO_InitTypeDef The_Buzzer;
	The_Buzzer.GPIO_Mode = GPIO_Mode_Out_PP;
	The_Buzzer.GPIO_Pin = GPIO_Pin_12;
	The_Buzzer.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &The_Buzzer);
	//******************************************
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Turn(void)//调用这个函数LED1状态取反
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	}
}