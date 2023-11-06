#include "stm32f10x.h"                  // Device header

#define BUZZER_Pin   GPIO_Pin_12
#define GPIO_BUZZER_Use  GPIOB

void BUZZER_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//
	
	//********************************************
	GPIO_InitTypeDef The_BUZZER;
	The_BUZZER.GPIO_Mode = GPIO_Mode_Out_PP;
	The_BUZZER.GPIO_Pin = BUZZER_Pin;
	The_BUZZER.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_BUZZER_Use, &The_BUZZER);
	//******************************************
	
	GPIO_SetBits(GPIO_BUZZER_Use,BUZZER_Pin);
	
}


void BUZZER_ON(void)
{
	GPIO_ResetBits(GPIO_BUZZER_Use, BUZZER_Pin);
}

void BUZZER_OFF(void)
{
	GPIO_SetBits(GPIO_BUZZER_Use, BUZZER_Pin);
}


void BUZZER_Turn(void)//调用这个函数状态取反
{
	if(GPIO_ReadOutputDataBit(GPIO_BUZZER_Use,BUZZER_Pin) == 0)
	{
		GPIO_SetBits(GPIO_BUZZER_Use,BUZZER_Pin);
	}
	else
	{
		GPIO_ResetBits(GPIO_BUZZER_Use,BUZZER_Pin);
	}
}