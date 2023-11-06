#include "stm32f10x.h"                  // Device header

#define Pin_A  GPIO_Pin_0
#define Pin_B  GPIO_Pin_1
#define GPIO_PinSourceA GPIO_PinSource0
#define GPIO_PinSourceB GPIO_PinSource1
#define EXTI_LineA EXTI_Line0
#define EXTI_LineB EXTI_Line1

int16_t Encoder_Count;



void Encoder_Init(void)
{
	//**配置初始化时钟外设
	//*配置GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//**配置GOIP
	//*定义结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = Pin_A | Pin_B;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*调用GPIOInit函数
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//**配置AFIO函数
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSourceA);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSourceB);
	//** 配置EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	//*定义一个结构体
	EXTI_InitStruct.EXTI_Line = EXTI_LineA | EXTI_LineB;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*触发沿的选择是上升沿还是下降沿，或者双边沿
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//*结构体初始化
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**配置NVIC
	//*优先级分组
	//*分组方式整个代码只能使用一种，执行一次就可以了
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC结构体定义
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
}

int16_t Get_Encoder_Count(void)
{
	uint16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;//返回一个变化的值
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, Pin_A) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, Pin_B) == 0)
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
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, Pin_B) == 0)
		{
			if (GPIO_ReadInputDataBit(GPIOB, Pin_A) == 0)
			{
				Encoder_Count ++;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

//中断函数1不要dely   2不要调用和主函数相同的硬件
