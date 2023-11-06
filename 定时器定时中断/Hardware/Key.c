#include "stm32f10x.h"                  // Device header
#include "Delay.h"
extern uint8_t Key_Num;

void Key_Init(void)
{
	//**配置初始化时钟外设
	//*配置GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//**配置GOIP
	//*定义结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*调用GPIOInit函数
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	//**配置AFIO函数
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
	//** 配置EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	//*定义一个结构体
	EXTI_InitStruct.EXTI_Line = EXTI_Line2 | EXTI_Line3;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*触发沿的选择是上升沿还是下降沿，或者双边沿
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	//*结构体初始化
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**配置NVIC
	//*优先级分组
	//*分组方式整个代码只能使用一种，执行一次就可以了
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC结构体定义
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
//	//都初始化为上拉输入的模式
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
	//读取按键情况的函数
//uint8_t Key_GetNum(void)
//{
//	//用到读取GPIO端口的功能
//	
//	
//	uint8_t Key_Num = 0;
//	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1 ) == 0)
//	{
//		Delay_ms(20);//消除抖动
//		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);//按下后没有松手将会卡在这里
//		Delay_ms(20);//消除松手时的抖动
//		Key_Num = 1;
//	}
//	
//	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
//	{
//		Delay_ms(20);//消除抖动
//		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);//按下后没有松手将会卡在这里
//		Delay_ms(20);//消除松手时的抖动
//		Key_Num = 2;
//	}
//	return Key_Num;
//}



uint8_t EXTI2_IRQHandler(void)
{
	//用到读取GPIO端口的功能
	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2 ) == 0)
	{
		Delay_ms(20);//消除抖动
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0);//按下后没有松手将会卡在这里
		Delay_ms(20);//消除松手时的抖动
		Key_Num = 2;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
	return Key_Num;
}

uint8_t EXTI3_IRQHandler(void)
{
	//用到读取GPIO端口的功能
	if( GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3 ) == 0)
	{
		Delay_ms(20);//消除抖动
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0);//按下后没有松手将会卡在这里
		Delay_ms(20);//消除松手时的抖动
		Key_Num = 3;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
	return Key_Num;
}








