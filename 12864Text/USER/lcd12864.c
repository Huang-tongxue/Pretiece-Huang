/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��lcd12864.c
 * ����    ��lcd12864 Ӧ�ú�����
 *          
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
																				 
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
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); //�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );	//ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;        //�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;        //��������
																				//	�����ɼ򵥷�Ϊ���� ��GND�ͽ�VCC���ֱ���������������������
																				//	����
																				//	�������� Ĭ��ΪH�������������� IO+����+GND �½��ش���
																				//	�������� Ĭ��λL�������������� IO+����+VCC �����ش���
	GPIO_Init(GPIOA, &GPIO_InitStructure);//�����趨������ʼ��GPIOA
	
	EXTI_ClearITPendingBit(EXTI_Line11); 					//��� EXTI 11 ��·����λ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11); //ѡ�� GPIO A .11�ܽ������ⲿ�ж���·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //		���� EXTI ��·Ϊ  �ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //	����������·������Ϊ�ж�����
	EXTI_InitStructure.EXTI_Line = EXTI_Line11 ; //		EXTI_Line ѡ���˴�ʹ�ܻ���ʧ�ܵ��ⲿ��·
	EXTI_InitStructure.EXTI_LineCmd = ENABLE; //		
	EXTI_Init(&EXTI_InitStructure);		//��ʼ���ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//ʹ���ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�2  ��ΪΪ����Ϊ2 �����������Ϊ0-3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);    //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

void EXTI15_10_IRQHander()
{
	delay_ms(10);
//	if(Page_Down==1)
//	{
//		PageDown_12864(str);
//	}
	EXTI_ClearITPendingBit(EXTI_Line11); 					//��� EXTI 11 ��·����λ
}
/****************************************************************
                     �������ݴ���
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
                     дָ���
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
                     д���ݺ���
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
                     ��x��y��д����
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
                     д���ֺ��� 
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
                     ��ͼ����  ���У�˳��8*16
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
	
  for(i=0;i<32;i++)  //���ϰ���
  {
	write_com(0x80+i);
	write_com(0x80);
	for(j=0;j<16;j++)
	{
	  write_data(*p++);
	}
  }
	
  for(i=0;i<32;i++)  //���°���
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
                     ��ʼ�� LCM
****************************************************************/
void LCD12864_Init(void)
{
  write_com(0x30);  //�����趨��8λ�ӿڿ���λ������ָ�
  delay_us(5);
  write_com(0x0c);  //��ʾ�������ã�������ʾ�����α���ʾ�أ�������ʾ
  delay_us(5);
  write_com(0x01);  //�����ʾ 
  delay_us(5);
}
/****************************************************************
                     ��ҳ����
****************************************************************/
void PageDown_12864(u8 *ser)
{
	u8 i,addr,flag,hang,over,*ptdat;
	ptdat = ser; //����ַ����׵�ַ
	over = 0; //д����ַ�����д���ַ�������Ŀ��ʼ��Ϊ0
	while(1){
	
	write_com(0x80); //д��һ���ַ�
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
	
	write_com(0x90); //д�ڶ����ַ�
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
	
	write_com(0x88); //д�������ַ�
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
	
	write_com(0x98); //д�������ַ�
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
                     ��������
****************************************************************/
void scroll_12864(u8 *ser)
{	     
	unsigned char i,addr,flag,hang,over,*ptdat;
				//addr�洢��ַ���м������flag������ַ��hangҪд���ݵ��У�
       //overд���ַ��������д�Ŀ��ַ�����
	ptdat = ser; //����ַ����׵�ַ
	over = 0; //д����ַ�����д���ַ�������Ŀ��ʼ��Ϊ0
	
	write_com(0x80); //д��һ���ַ�
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
	
	write_com(0x90); //д�ڶ����ַ�
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
	
	write_com(0x88); //д�������ַ�
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
	
	write_com(0x98); //д�������ַ�
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
	write_com(0xa0); 		//д������DDRAM,д������Ϊ�������ַ����͵������ַ���
	for(i = 0; i < 16; i++)
	{ 										//д�������ַ���
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
	{							 //д�������ַ���
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
	
	write_com(0x0c); //����ʾ
	if(over > 15){;} //��ʾ�ַ�����4�У�����
	else //��ʾ�ַ�����4�У�����д�ַ���ͬʱ������
	{
		hang = 4;
		flag = 0x01;
		while(1)
			{
			switch(hang){   //����д��DDRAM�ĵ�ַ
				case 1: addr = 0x80; break;
				case 2: addr = 0x90; break;
				case 3: addr = 0xa0; break;
				case 4: addr = 0xb0; break;
									}
			
			switch(hang){ //����Ҫд���ݵ���һ��
				case 1: hang = 2; break;
				case 2: hang = 3; break;
				case 3: hang = 4; break;
				case 4: hang = 1; break;
									}
			ptdat = ptdat - 32;
			for(i = 0; i < 8; i++)
			{
				write_com(0x34); //����չָ��
				write_com(0x03); //�����������ַ
				write_com(0x40 + flag++); //���þ���ַ
				write_com(0x30);       //�ص�����ָ��
				write_com(addr + i);
				delay_ms(100); 
			if(*ptdat != '\0')
				{
					write_data(*ptdat++);   //����д�������ֽ�֮���ֽ�
				}
			else
				{
					SandByte(0x20);
				}
			if(*ptdat != '\0')
				{
					write_data(*ptdat++);   //����д�������ֽ�֮���ֽ�
				}
				else
				{
					SandByte(0x20);
				}
			}
			ptdat = ptdat + 16;
			for(i = 8; i < 16; i++)
			{
				write_com(0x34); //����չָ��
				write_com(0x03); //�����������ַ
				if(flag == 64){flag = 0;}
				write_com(0x40 + flag); //���þ���ַ
				flag++;
				write_com(0x30); //�ص�����ָ��
				write_com(addr + i);
				delay_ms(100); 
				if(*ptdat != '\0')
					{
						write_data(*ptdat++);  //����д�������ֽ�֮���ֽ�
					}
					else{
						over++;  //д�����һ���ַ�����Ҫ�پ�16�β�����ʾ������
						SandByte(0x20);
							}
				if(*ptdat != '\0')
					{
						write_data(*ptdat++);   //����д�������ֽ�֮���ֽ�
					}
					else{
						SandByte(0x20);
							}
			}
			if(over < 8){;}   //���һ����ʾ�����ֹͣ��
			else {break;}
						}
	}
}


















