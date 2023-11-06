#ifndef _LCD12864_H_
#define _LCD12864_H_

typedef struct
{
	u8 com; 
	u8 num; 
	u8 *dat;
}LCD_InitTypeDef;


#define DATA 0x00FF
#define DATA_PROT GPIOC

#define RS GPIO_Pin_3
#define RW GPIO_Pin_7//GND
#define EN GPIO_Pin_8
#define PS GPIO_Pin_9
#define CMD_PROT GPIOA

#define RS_HIGH GPIO_SetBits(CMD_PROT,RS)
#define RS_LOW  GPIO_ResetBits(CMD_PROT,RS)

#define RW_HIGH GPIO_SetBits(CMD_PROT,RW)
#define RW_LOW  GPIO_ResetBits(CMD_PROT,RW)

#define EN_HIGH GPIO_SetBits(CMD_PROT,EN)
#define EN_LOW  GPIO_ResetBits(CMD_PROT,EN)

#define PS_HIGH GPIO_SetBits(CMD_PROT,PS)
#define PS_LOW  GPIO_ResetBits(CMD_PROT,PS)

#define CMD  0
#define DAT 1


void LCD12864_UserConfig(void);
void LCD12864_Write_Cmd_Data(u8 cmd,u8 data);
void LCD12864_Write_Init(void);
void LCD12864_Open(void);
void LCD12864_Shut(void);
void LCD12864_Write_Word(LCD_InitTypeDef LCD_InitStructure);



#endif