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
unsigned char code buf[4] ={0xbb,0xb6,0xd3,0xad};//欢迎

#define DATA       P2          //P2接数据口
#define CONTROL P0
#define E    7           //并行的使能信号        sbit E   = P0^7 
#define RW   6          //并行的读写信号         sbit RW = P0^6 
#define RS   5         //并行的指令数据选择信号 sbit RS = P0^5   
#define PSB 4         //并/串行接口选择         sbit PSB = P0^4
#define RST 3         //复位 低电平有效         sbit RST = P0^3
#define SETB(x,y) (x|=(1<<y))          //设置第x位为1
#define CLRB(x,y) (x&=(~(1<<y)))       //设置第x位为0
#define CHKB(x,y) (x&(1<<y))

/********************测忙碌**********************/
//测忙碌子程序
//RS=0,RW=1,E=H,D0-D7=状态字
/************************************************/
void chek_busy(void)
{ unsigned char temp1;//状态信息（判断是否忙） 
   CLRB(CONTROL,RS);    // RS = 0;
   SETB(CONTROL,RW);    // RW = 1;
   SETB(CONTROL,E);    // E = 1;
   do{temp1 = DATA;DATA=0xFF;} while(temp1&0x80);//?？？？？？
   SETB(CONTROL,E);   // E = 1;
   DATA=0xFF;
}
/********************写命令**********************/
//写命令子程序
//
/************************************************/
void send_com(unsigned char cmd)/*写命令*/
{ 
chek_busy();
CLRB(CONTROL,RS); //RS = 0;
CLRB(CONTROL,RW); //RW = 0;
DATA = cmd;
SETB(CONTROL,E); //E = 1;
CLRB(CONTROL,E); //E = 0;
}
/********************写数据**********************/
//写数据子程序
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
/********************初始化**********************/
//复位、通讯方式选择
/************************************************/
void lcd_init(void)
{ 
    SETB(CONTROL,RST);//复位RST=1    ?
    SETB(CONTROL,PSB);       //通讯方式为并口PSB = 1
      //send_com(0x34);//34H--扩充指令操作
send_com(0x30);//功能设置，一次送8位数据，基本指令集
send_com(0x0C);//0000,1100 整体显示，游标off，游标位置off
send_com(0x01);//0000,0001 清DDRAM
send_com(0x02);//0000,0010 DDRAM地址归位
send_com(0x80);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器AC
}

/*******************************************************************/
//          设置显示位置    xpos(1~16),ypos(1~4)
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
//          在指定位置显示字符串
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
/********************写字符串******************/
//写字符串子程序
//xpos1取0～7共八列，ypos1取0～3共四行。
/**********************************************/
    void printstr(unsigned char xpos,unsigned char ypos,unsigned char str[],unsigned char k)
{ unsigned char n;
     switch (ypos)    // ？？？？？？下面有错，应0-3？
    { case 1: xpos |= 0x80;break;         //第一行
      case 2: xpos |= 0x90;break;         //第二行
      case 3: xpos |= 0x88;break;         //第三行
      case 4: xpos |= 0x98;break;         //第四行
      default: break;
     }
      send_com(xpos);                                    //此处的Xpos已转换为LCM的显示寄存器实际地址    ?????????????
      for(n=0;n < k;n++)
     { 
      send_data(str[n]);//显示汉字时注意码值，连续两个码表示一个汉字
      }
   }
/********************清屏************************/
//清屏
/************************************************/
void clr_lcd(void)
{
   send_com(0x01);
   //send_com(0x34);
   //send_com(0x30);
}
/**************主函数***********************/
void main ()
{ 
lcd_init();     //设定液晶工作方式
printstr(1,1,buf,4);//xpos应为偶数
print(5,1,"光临");//xpos应为偶数
print(0,3," SEEGU百度空间");//xpos应为偶数
while(1) { }
}

