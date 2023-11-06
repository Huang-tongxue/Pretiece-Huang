/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：lcd12864.c
 * 描述    ：lcd12864 应用函数库
 *          
 * 实验平台：CEPARK多功能开发学习板
																				 
**********************************************************************************/

#include "2lcd12864.h"	 
#include "delay.h"	
#include "stm32f10x_exti.h"	
extern uint8_t str[];

void LCD12864_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10  ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}
void  KEY_EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); //外部中断，需要使能AFIO时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );	//使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        //端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;        //下拉输入
																				//	按键可简单分为两种 接GND和接VCC，分别对用上拉输入和下拉输入
																				//	即：
																				//	上拉输入 默认为H，按键按下拉低 IO+按键+GND 下降沿触发
																				//	下拉输入 默认位L，按键按下拉高 IO+按键+VCC 上升沿触发
	GPIO_Init(GPIOA, &GPIO_InitStructure);//根据设定参数初始化GPIOA
	
	EXTI_ClearITPendingBit(EXTI_Line11); 					//清除 EXTI 11 线路挂起位
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11); //选择 GPIO A .11管脚用作外部中断线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //		设置 EXTI 线路为  中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //	设置输入线路上升沿为中断请求
	EXTI_InitStructure.EXTI_Line = EXTI_Line11 ; //		EXTI_Line 选择了待使能或者失能的外部线路
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; //		
	EXTI_Init(&EXTI_InitStructure);		//初始化中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//使能外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级2  因为为分组为2 这里可以设置为0-3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);    //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}

void EXTI15_10_IRQHander()
{
	delay_ms(10);
//	if(Page_Down==1)
//	{
//		PageDown_12864(str);
//	}
	EXTI_ClearITPendingBit(EXTI_Line11); 					//清除 EXTI 11 线路挂起位
}
/****************************************************************
                     串行数据传送
****************************************************************/
void  SandByte(u8 bye)
{
  u8  t;
  for(t=8;t>0;t--)
  {
	SCLK_Clr();
	if(bye & 0x80) SID_Set();
		     else  SID_Clr();
	bye=bye<<1;
    delay_us(2);
    SCLK_Set();
  }
}
/****************************************************************
                     写指令函数
****************************************************************/
void write_com(u8 com)
{
  CS_Set();
  SandByte(0xf8);
  //delay_us(10);
  SandByte(com&0xf0);
  //delay_us(10);
  SandByte(com << 4);
  //delay_us(10);
  CS_Clr();
}
/****************************************************************
                     写数据函数
****************************************************************/
void write_data(u8 data)
{
  CS_Set();
  SandByte(0xfa);
  //delay_us(10);
  SandByte(data&0xf0);
  //delay_us(10);
  SandByte(data << 4);
 // delay_us(10);
  CS_Clr();
}
/****************************************************************
                     在x行y列写汉字
****************************************************************/
void   lcd_pos(u8 y,u8 x) // x:0~3;y:0~7
{
  switch(y)
  {
    case 0: write_com(0x80+x);break;
	case 1: write_com(0x90+x);break;
    case 2: write_com(0x88+x);break;
	case 3: write_com(0x98+x);break;
  }
}
/****************************************************************
                     写汉字函数 
****************************************************************/
void  write_hz(const u8 *str)
{
  while(*str>0)
  {
    write_data(*str);
	str++;
  }
}
/****************************************************************
                     画图函数  逐行，顺向，8*16
****************************************************************/
void drawpic(const u8 *p)
{
  u8 i, j ;
  write_com(0x36);
  delay_ms(2);
  write_com(0x36);
  delay_ms(2);
  write_com(0x3e);
  delay_ms(2);
  write_com(0x01);
	
  for(i=0;i<32;i++)  //画上半屏
  {
	write_com(0x80+i);
	write_com(0x80);
	for(j=0;j<16;j++)
	{
	  write_data(*p++);
	}
  }
	
  for(i=0;i<32;i++)  //画下半屏
  {
	write_com(0x80+i);
	write_com(0x88);
	for(j=0;j<16;j++)
	{
	  write_data(*p++);
	}
  }
}
/****************************************************************
                     初始化 LCM
****************************************************************/
void LCD12864_Init(void)
{
  write_com(0x30);  //功能设定：8位接口控制位，基本指令集
  delay_us(5);
  write_com(0x0c);  //显示开关设置：整体显示开，游标显示关，正常显示
  delay_us(5);
  write_com(0x01);  //清除显示 
  delay_us(5);
}
/****************************************************************
                     翻页函数
****************************************************************/
void PageDown_12864(u8 *ser)
{
	u8 i,addr,flag,hang,over,*ptdat;
	ptdat = ser; //获得字符串首地址
	over = 0; //写入空字符串（写完字符串后）数目初始化为0
	while(1){
	
	write_com(0x80); //写第一行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x90); //写第二行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x88); //写第三行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x98); //写第四行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}	
	if(Page_Down==0)
	{
			ptdat = ptdat - 64; 
			delay_ms(8000);
	}
	else
		{
				ptdat = ptdat + 64; 
		}
	}
}

/****************************************************************
                     滚动函数
****************************************************************/
void scroll_12864(u8 *ser)
{	     
	unsigned char i,addr,flag,hang,over,*ptdat;
				//addr存储地址的中间变量，flag卷屏地址，hang要写数据的行，
       //over写完字符串后继续写的空字符计数
	ptdat = ser; //获得字符串首地址
	over = 0; //写入空字符串（写完字符串后）数目初始化为0
	
	write_com(0x80); //写第一行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x90); //写第二行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x88); //写第三行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	write_com(0x98); //写第四行字符
	for(i = 0; i < 16; i++)
	{
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
		else{
			SandByte(0x20);
			over++;
				}
	}
	
	ptdat = ptdat - 32;
	write_com(0xa0); 		//写第三行DDRAM,写入内容为第三行字符串和第五行字符串
	for(i = 0; i < 16; i++)
	{ 										//写第三行字符串
		if(*ptdat != '\0')
			{
			write_data(*ptdat++);
			}
			else
				{
					SandByte(0x20);
					over++;
				}
	}
	
	ptdat = ptdat + 16;
	for(i = 0; i < 16; i++)
	{							 //写第五行字符串
		if(*ptdat != '\0')
			{
		write_data(*ptdat++);
			}
			else
				{
					SandByte(0x20);
					over++;
				}
	}
	
	write_com(0x0c); //开显示
	if(over > 15){;} //显示字符不足4行，不卷动
	else //显示字符大于4行，继续写字符，同时开启卷动
	{
		hang = 4;
		flag = 0x01;
		while(1)
			{
			switch(hang){   //设置写入DDRAM的地址
				case 1: addr = 0x80; break;
				case 2: addr = 0x90; break;
				case 3: addr = 0xa0; break;
				case 4: addr = 0xb0; break;
									}
			
			switch(hang){ //设置要写数据的下一行
				case 1: hang = 2; break;
				case 2: hang = 3; break;
				case 3: hang = 4; break;
				case 4: hang = 1; break;
									}
			ptdat = ptdat - 32;
			for(i = 0; i < 8; i++)
			{
				write_com(0x34); //打开扩展指令
				write_com(0x03); //允许输入卷动地址
				write_com(0x40 + flag++); //设置卷动地址
				write_com(0x30);       //回到基本指令
				write_com(addr + i);
				delay_ms(100); 
			if(*ptdat != '\0')
				{
					write_data(*ptdat++);   //连续写入两个字节之高字节
				}
			else
				{
					SandByte(0x20);
				}
			if(*ptdat != '\0')
				{
					write_data(*ptdat++);   //连续写入两个字节之低字节
				}
				else
				{
					SandByte(0x20);
				}
			}
			ptdat = ptdat + 16;
			for(i = 8; i < 16; i++)
			{
				write_com(0x34); //打开扩展指令
				write_com(0x03); //允许输入卷动地址
				if(flag == 64){flag = 0;}
				write_com(0x40 + flag); //设置卷动地址
				flag++;
				write_com(0x30); //回到基本指令
				write_com(addr + i);
				delay_ms(100); 
				if(*ptdat != '\0')
					{
						write_data(*ptdat++);  //连续写入两个字节之高字节
					}
					else{
						over++;  //写完最后一行字符，需要再卷动16次才能显示出来。
						SandByte(0x20);
							}
				if(*ptdat != '\0')
					{
						write_data(*ptdat++);   //连续写入两个字节之低字节
					}
					else{
						SandByte(0x20);
							}
			}
			if(over < 8){;}   //最后一行显示完毕则停止卷动
			else {break;}
						}
	}
}


















