#include "stm32f10x.h"                  // Device header


//LED初始化函数


void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//
	
	//********************************************
	GPIO_InitTypeDef The_2_LED;
	The_2_LED.GPIO_Mode = GPIO_Mode_Out_PP;
	The_2_LED.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	The_2_LED.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &The_2_LED);
	//******************************************
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
	
}


void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}


void LED1_Turn(void)//调用这个函数LED1状态取反
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

void LED2_Turn(void)//调用这个函数LED1状态取反
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
}