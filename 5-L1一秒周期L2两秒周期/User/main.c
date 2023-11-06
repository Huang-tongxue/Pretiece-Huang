#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//初始化时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体填充参数2
	//初始化结构体成员
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//直接全部引脚初始化为推挽输出模式GPIO_Pin_01 | GPIO_Pin_02 | GPIO_Pin_03
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	uint16_t LED;
	LED = 0x0000;
	while (1)
	{
		GPIO_Write(GPIOA, ~LED);//C语言不支持二进制这里用十六进制表示
		//加入按位取反符号，只有第一个点亮，其他的熄灭
		Delay_ms(500);
		LED++;
		if(LED > 0x0003)
			LED = 0x0000;


	}
}
