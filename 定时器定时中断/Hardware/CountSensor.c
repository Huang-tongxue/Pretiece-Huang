#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	//**配置初始化时钟外设
	//*配置GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//*配置AFIO（其初始化函数也存放在GPIO头文件里）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	
	//**配置GOIP
	//*定义结构体
	GPIO_InitTypeDef GPIO_InitStruct;
	//*引脚选择14号口
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	//*这里的输入模式应该查询文档看复合要求的是哪种类型
	//*上拉输入，浮空输入，下拉输入都可以，这里选择上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//*调用GPIOInit函数
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	
	//**配置AFIO函数
	//*EXTI外部引脚选择
	//*选择B和14线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	//** 配置EXTI
	//*这四个都是对状态寄存器的读取
	//*FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
	//*void EXTI_ClearFlag(uint32_t EXTI_Line);
	//*下面两个对中断是否允许做出了判断
	//*ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
	//*void EXTI_ClearITPendingBit(uint32_t EXTI_Line);
	EXTI_InitTypeDef EXTI_InitStruct;
	//*定义一个结构体
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	//*触发沿的选择是上升沿还是下降沿，或者双边沿
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	//*结构体初始化
	EXTI_Init(&EXTI_InitStruct);
	
	
	
	//**配置NVIC
	//*因为NVIC是内核外设，函数被放在杂项里
	//*misc. h
	//*中断分组
	//*void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
	//*void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
	//*设置中断向量表
	//*void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
	//*void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
	//*void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
	
	//*优先级分组
	//*分组方式整个代码只能使用一种，执行一次就可以了
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//*NVIC结构体定义
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
//**中断函数
void EXTI15_10_IRQHandler(void)//名词来源于启动文件
{
	//**进行中断标志位的判断
	//*10和15都能进来，所以要判断是不是所需的信号源来的
	if(EXTI_GetITStatus( EXTI_Line14) == SET)
	{
//		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
//		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
//		{
//			CountSensor_Count ++;
//		}
		CountSensor_Count ++;
		//*清除中断标志位
		EXTI_ClearITPendingBit( EXTI_Line14);
	}
	
}