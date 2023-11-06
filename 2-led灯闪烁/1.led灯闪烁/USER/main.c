#include "stm32f10x.h"                  // Device header
   // Device header
#include "Delay.h"
GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体

#define GPIO_LED1  GPIO_Pin_0
#define GPIO_USE   GPIOA

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//配置初始化时钟
	

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_LED1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, 1);
	while(1)
{
//  方法二
//	GPIO_SetBits(GPIOA,GPIO_LED1);
//	GPIO_ResetBits(GPIOA,GPIO_LED1);
	
	GPIO_WriteBit(GPIOA,GPIO_Pin_0, Bit_SET);
			Delay_ms(1000);
 GPIO_WriteBit(GPIOA,GPIO_Pin_0, Bit_RESET);
			Delay_ms(1000);
}
}
