#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"


uint8_t Key_Num;//定义一个全局变量，用于存放返回值

int main(void)
{
	
	
	LED_Init();
	Key_Init();
	while (1)
	{
		Key_Num = Key_GetNum();
		if(Key_Num == 1)
		{
			LED1_Turn();
		}
		if(Key_Num == 2)
		{
			LED2_Turn();
		}
	}
	
}
