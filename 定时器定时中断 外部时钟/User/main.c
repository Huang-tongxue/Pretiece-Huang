#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
//#include "Key.h"
#include "OLED.h"
#include "Timer.h"

uint8_t Key_Num;//定义一个全局变量，用于存放返回值
uint16_t NUM;//extern声明变量使得可以跨越C文件使用变量
int main(void)
{
	Timer_Init();
	OLED_Init();
	//*******************
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体填充参数2
	//初始化结构体成员
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//直接全部引脚初始化为推挽输出模式GPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	OLED_ShowString(1,1,"Num:");
	OLED_ShowString(2,1,"CNT:");

	while(1)
	{
		OLED_ShowNum(1,5,NUM,5);
		OLED_ShowNum(2,5,Timer_GetCounter(),5);
	}
	
	
	

}		
		
		
		//*************************
//		char arr[13] = "Hello World !";
//		short row = 1;
//		short col = 1;
//		while(col <= 13)
//		{
//			OLED_ShowChar(1, col,arr[col - 1]);
//			Delay_ms(300);
//			col++;
//		}
//		col = 1;
//		while(col <= 13)
//		{
//			OLED_ShowChar(1, col, ' ');
//			Delay_ms(300);
//			col++;
//		}
		
		
		
//**********************************
//		int i = 1;
//		while(i)
//		{
//			++i;
//			if(i % 2 == 1)
//			{
//				OLED_ShowString(1,1,"HELLO WORLD  ");
//				OLED_ShowNum(2,1,230918,12);
//				OLED_ShowString(3,1,"I Like STM32");
//				OLED_ShowString(4,1,"^o^         ");
//				Delay_ms(2000);
//			}
//			if(i % 2 == 0)
//			{
//				OLED_ShowString(1,1,"************");
//				OLED_ShowString(2,1,"************");
//				OLED_ShowString(3,1,"************");
//				OLED_ShowString(4,1,"************");
//				Delay_ms(2000);
//			}
//		}


//	}
	
//}











