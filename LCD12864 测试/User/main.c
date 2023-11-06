#include "stm32f10x.h"                  // Device header

#include<reg52.h>
#include <math.h>
void lcd_init(void);
void clr_lcd(void);
void send_com(unsigned char cmd);
void send_data(unsigned char dat);
void chek_busy(void);
void set_xy(unsigned char xpos,unsigned char ypos); 
void print(unsigned char x,unsigned char y,char* str);
void printstr(unsigned char xpos,unsigned char ypos,unsigned char str[],unsigned char k);
unsigned char code buf[4] ={0xbb,0xb6,0xd3,0xad};//��ӭ

#define DATA       P2          //P2�����ݿ�
#define CONTROL P0
#define E    7           //���е�ʹ���ź�        sbit E   = P0^7 
#define RW   6          //���еĶ�д�ź�         sbit RW = P0^6 
#define RS   5         //���е�ָ������ѡ���ź� sbit RS = P0^5   
#define PSB 4         //��/���нӿ�ѡ��         sbit PSB = P0^4
#define RST 3         //��λ �͵�ƽ��Ч         sbit RST = P0^3
#define SETB(x,y) (x|=(1<<y))          //���õ�xλΪ1
#define CLRB(x,y) (x&=(~(1<<y)))       //���õ�xλΪ0
#define CHKB(x,y) (x&(1<<y))

/********************��æµ**********************/
//��æµ�ӳ���
//RS=0,RW=1,E=H,D0-D7=״̬��
/************************************************/
void chek_busy(void)
{ unsigned char temp1;//״̬��Ϣ���ж��Ƿ�æ�� 
   CLRB(CONTROL,RS);    // RS = 0;
   SETB(CONTROL,RW);    // RW = 1;
   SETB(CONTROL,E);    // E = 1;
   do{temp1 = DATA;DATA=0xFF;} while(temp1&0x80);//?����������
   SETB(CONTROL,E);   // E = 1;
   DATA=0xFF;
}
/********************д����**********************/
//д�����ӳ���
//
/************************************************/
void send_com(unsigned char cmd)/*д����*/
{ 
chek_busy();
CLRB(CONTROL,RS); //RS = 0;
CLRB(CONTROL,RW); //RW = 0;
DATA = cmd;
SETB(CONTROL,E); //E = 1;
CLRB(CONTROL,E); //E = 0;
}
/********************д����**********************/
//д�����ӳ���
//
/************************************************/
void send_data(unsigned char dat)
{ 
chek_busy();
SETB(CONTROL,RS); //RS = 1;
CLRB(CONTROL,RW); //RW = 0;
DATA = dat;
SETB(CONTROL,E); //E = 1;
CLRB(CONTROL,E); //E = 0;
}
/********************��ʼ��**********************/
//��λ��ͨѶ��ʽѡ��
/************************************************/
void lcd_init(void)
{ 
    SETB(CONTROL,RST);//��λRST=1    ?
    SETB(CONTROL,PSB);       //ͨѶ��ʽΪ����PSB = 1
      //send_com(0x34);//34H--����ָ�����
send_com(0x30);//�������ã�һ����8λ���ݣ�����ָ�
send_com(0x0C);//0000,1100 ������ʾ���α�off���α�λ��off
send_com(0x01);//0000,0001 ��DDRAM
send_com(0x02);//0000,0010 DDRAM��ַ��λ
send_com(0x80);//1000,0000 �趨DDRAM 7λ��ַ000��0000����ַ������AC
}

/*******************************************************************/
//          ������ʾλ��    xpos(1~16),ypos(1~4)
/*******************************************************************/
void set_xy(unsigned char xpos,unsigned char ypos)
{
switch(ypos)
{
   case 1:
    send_com(0X80|xpos);break;
   case 2:
    send_com(0X90|xpos);break;
   case 3:
    send_com(0X88|xpos);break;
   case 4:
    send_com(0X98|xpos);break;
   default:break;
}
}
/*******************************************************************/
//          ��ָ��λ����ʾ�ַ���
/*******************************************************************/
void print(unsigned char x,unsigned char y,char* str)
{ 
    unsigned char lcd_temp; 
    set_xy(x,y);
    lcd_temp=*str;
    while(lcd_temp != 0x00) 
    { 
        send_data(lcd_temp);
        lcd_temp=*(++str);
    } 
}
/********************д�ַ���******************/
//д�ַ����ӳ���
//xpos1ȡ0��7�����У�ypos1ȡ0��3�����С�
/**********************************************/
    void printstr(unsigned char xpos,unsigned char ypos,unsigned char str[],unsigned char k)
{ unsigned char n;
     switch (ypos)    // �����������������д�Ӧ0-3��
    { case 1: xpos |= 0x80;break;         //��һ��
      case 2: xpos |= 0x90;break;         //�ڶ���
      case 3: xpos |= 0x88;break;         //������
      case 4: xpos |= 0x98;break;         //������
      default: break;
     }
      send_com(xpos);                                    //�˴���Xpos��ת��ΪLCM����ʾ�Ĵ���ʵ�ʵ�ַ    ?????????????
      for(n=0;n < k;n++)
     { 
      send_data(str[n]);//��ʾ����ʱע����ֵ�������������ʾһ������
      }
   }
/********************����************************/
//����
/************************************************/
void clr_lcd(void)
{
   send_com(0x01);
   //send_com(0x34);
   //send_com(0x30);
}
/**************������***********************/
void main ()
{ 
lcd_init();     //�趨Һ��������ʽ
printstr(1,1,buf,4);//xposӦΪż��
print(5,1,"����");//xposӦΪż��
print(0,3," SEEGU�ٶȿռ�");//xposӦΪż��
while(1) { }
}

