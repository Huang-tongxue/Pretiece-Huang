#include "stm32f10x.h"                  // Device header
extern uint16_t NUM;//extern声明变量使得可以跨越C文件使用变量

void Timer_Init(void)//初始化定时器  
{
	//第一步开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//选择为内部时钟
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00F);//ETR引脚的外部时钟模式2配置
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStruct;
	TIM_TimBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1; 
	TIM_TimBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimBaseInitStruct.TIM_Period = 10 - 1;//需要小于65535
	TIM_TimBaseInitStruct.TIM_Prescaler = 1 - 1;//需要小于65535
	TIM_TimBaseInitStruct.TIM_RepetitionCounter = 0;

	
	TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStruct);TIM_ClearFlag(TIM2, TIM_FLAG_Update);//手动更新中断标志位清除
	//时基单元配置完成
	//使能更新中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启了更新中断到NVIC的通路
	//NVIC
	//优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择分组二
	NVIC_InitTypeDef NVIC_InitTypeDefStructer;
	NVIC_InitTypeDefStructer.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTypeDefStructer.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeDefStructer.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
	NVIC_InitTypeDefStructer.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitTypeDefStructer);
	//中断通道打通
	//最后一步，启动定时器
	TIM_Cmd(TIM12,ENABLE);
	
	
	
}


//中断函数
void TIM2_IQRHandler(void)
{
	//检查中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
	{
		NUM++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除标志位
	}
	
	
}


uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}