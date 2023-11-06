#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int16_t NUM;
int main(void)
{
	OLED_Init();
	Encoder_Init();
	
	
	OLED_ShowString(1,1,"Num:");
	while(1)
	{
		NUM += Get_Encoder_Count();
		OLED_ShowSignedNum(1,5,NUM,5);
	}
}
