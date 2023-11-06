#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	//都初始化为上拉输入的模式
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_Key;
	
	GPIO_Init_Key.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_Key.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_Init_Key.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_Init_Key);
	//****************************
	

}
	//读取按键情况的函数
uint8_t Key_GetNum(void)
{
	//用到读取GPIO端口的功能
	
	
	uint8_t Key_Num = 0;
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1 ) == 0)
	{
		Delay_ms(20);//消除抖动
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);//按下后没有松手将会卡在这里
		Delay_ms(20);//消除松手时的抖动
		Key_Num = 1;
	}
	
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(20);//消除抖动
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);//按下后没有松手将会卡在这里
		Delay_ms(20);//消除松手时的抖动
		Key_Num = 2;
	}
	return Key_Num;
}













