#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t Key_Num;//定义一个全局变量，用于存放返回值

int main(void)
{
	
	
	Buzzer_Init();
	LightSensor_Init();
	while (1)
	{
		if(LightSensor_Get() == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
		
	}
	
}
