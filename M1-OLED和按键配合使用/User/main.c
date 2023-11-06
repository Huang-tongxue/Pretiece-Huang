#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"

uint8_t Key_Num;//定义一个全局变量，用于存放返回值
uint8_t Menu = 0;
uint8_t OLED_TheMenu[4] = {1, 2, 3, 4};//存放界面

int main(void)
{
	Key_Init();
	OLED_Init();
	//*******************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体填充参数2
	//初始化结构体成员
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//直接全部引脚初始化为推挽输出模式GPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	//****************

	while (1)
	{
		if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1 ) == 0)
		{
			Delay_ms(20);//消除抖动
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0);//按下后没有松手将会卡在这里
			Delay_ms(20);//消除松手时的抖动
			Menu++;
			if(Menu == 4)
				Menu = 0;
			OLED_ShowMenu();
		}
		
		if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
		{
			Delay_ms(20);//消除抖动
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0);//按下后没有松手将会卡在这里
			Delay_ms(20);//消除松手时的抖动
			
			if(Menu != 0)
				Menu--;
			else
				Menu = 3;
			OLED_ShowMenu();
		}

	}
	
}
