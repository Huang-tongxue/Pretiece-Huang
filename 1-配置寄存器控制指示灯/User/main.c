#define USE_STDPERIPH_DRIVER
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"


uint8_t Key_Num;//����һ��ȫ�ֱ��������ڴ�ŷ���ֵ

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	

	GPIO_InitTypeDef Light13;
	Light13.GPIO_Mode=GPIO_Mode_Out_PP;
	Light13.GPIO_Pin=GPIO_Pin_13;
	Light13.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&Light13);
	
	

	while (1)
	{
			GPIO_SetBits(GPIOC,GPIO_Pin_13);//��PCʮ���ſ�����Ϊ�ߵ�ƽ
			Delay_ms(500);
			GPIO_ResetBits(GPIOC,GPIO_Pin_13);//��PCʮ���ſ�����Ϊ�͵�ƽ
			Delay_ms(500);
		
	}
	
}
