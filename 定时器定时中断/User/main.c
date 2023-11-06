#include "stm32f10x.h"                  // Device header
#include "Alarm.h"

uint16_t num = 0;
uint8_t Key_Num;

int main(void)
{
	Alarm_Init();
	
	while(1)
	{
		OLED_ShowString(1,1,"Settting Time:");
		OLED_ShowNum(2,1,num,5);
		num += Get_Encoder_Count();
	}
}		



//	Timer_Init();
//	OLED_Init();
//	//*******************
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟
//	
//	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体填充参数2
//	//初始化结构体成员
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//直接全部引脚初始化为推挽输出模式GPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
//	
//	OLED_ShowString(1,1,"Num:");
//	while(1)
//	{
//		OLED_ShowNum(1,5,NUM,5);
//		OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
//	}
	
