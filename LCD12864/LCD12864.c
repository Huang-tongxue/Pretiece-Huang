#include "stm32f10x.h"                  // Device header
#include "lcd12864.h"
#include "Delay.h"


void LCD12864_UserConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin   = DATA;             //DATA
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init( DATA_PROT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=RS | RW | EN | PS;     //CMD
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(CMD_PROT,&GPIO_InitStruct);
}
void LCD12864_Write_Cmd_Data(u8 cmd,u8 data)
{
	(cmd) ? RS_HIGH : RS_LOW;
	
	
	RW_LOW;
	EN_LOW;
	GPIO_Write(DATA_PROT,data);
	Delay_ms(2);
	EN_HIGH;//把数据送出去
	Delay_ms(2);
	EN_LOW;
	
	
	
}
void LCD12864_Write_Init(void)
{
	PS_HIGH;
	
	LCD12864_Write_Cmd_Data(CMD,0x30);
	LCD12864_Write_Cmd_Data(CMD,0x06);
	LCD12864_Write_Cmd_Data(CMD,0x0C);
	LCD12864_Write_Cmd_Data(CMD,0x01);
	LCD12864_Write_Cmd_Data(CMD,0x80);	
}
void LCD12864_Open(void)
{
	LCD12864_Write_Cmd_Data(CMD,0x0C);
}
void LCD12864_Shut(void)
{
	LCD12864_Write_Cmd_Data(CMD,0x08);
}
void LCD12864_Write_Word(LCD_InitTypeDef LCD_InitStructure)
{
	LCD12864_Write_Cmd_Data(CMD,LCD_InitStructure.com);
	
	for(u8 i=0;i<LCD_InitStructure.num;i++)
	{
		LCD12864_Write_Cmd_Data(DAT,*LCD_InitStructure.dat++);
	}
}

