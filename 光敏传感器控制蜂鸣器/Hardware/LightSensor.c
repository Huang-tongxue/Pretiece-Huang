#include "stm32f10x.h"                  // Device header
void LightSensor_Init(void)
{
	//都初始化为上拉输入的模式
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Init_LightSensor;
	
	GPIO_Init_LightSensor.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init_LightSensor.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init_LightSensor.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_Init_LightSensor);
	//****************************
	

}	

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}