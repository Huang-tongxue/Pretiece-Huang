#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
//#include "Key.h"
#include "OLED.h"
#include "LCD12864.h"

LCD_InitTypeDef LCD_InitStructure;

int main(void)
{
	SystemInit();
	//Delay_Init();
	LCD12864_UserConfig();
    LCD12864_Write_Init();
	
	LCD_InitStructure.com=0X80;  //0x80-0x8f  上半屏  16个字符 8个汉字
	LCD_InitStructure.num=16;
	LCD_InitStructure.dat=(u8*)&"胜日寻芳泗水滨,";
	LCD12864_Write_Word(LCD_InitStructure);
    
	LCD_InitStructure.com=0X90;  //0x80-0x8f  上半屏  16个字符 8个汉字
	LCD_InitStructure.num=16;
	LCD_InitStructure.dat=(u8*)&"无边光景一时新.";
	LCD12864_Write_Word(LCD_InitStructure);
	
	LCD_InitStructure.com=0X88;  //0x88-0x97  上半屏  16个字符 8个汉字
	LCD_InitStructure.num=16;
	LCD_InitStructure.dat=(u8*)&"等闲识得东风面,";
	LCD12864_Write_Word(LCD_InitStructure);
	
	LCD_InitStructure.com=0X98;  //0x98-0xA7  上半屏  16个字符 8个汉字
	LCD_InitStructure.num=16;
	LCD_InitStructure.dat=(u8*)&"万紫千红总是春.";
	LCD12864_Write_Word(LCD_InitStructure);
	
	while(1)
	{
		
	}
}

