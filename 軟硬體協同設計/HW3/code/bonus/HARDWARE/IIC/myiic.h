#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//IIC 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/6
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
   	   		   
//IO方向設置
#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9輸入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9輸出模式
//IO操作函數	 
#define IIC_SCL    PBout(8) //SCL
#define IIC_SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //輸入SDA 

#define SDA1_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PB7輸入模式
#define SDA1_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} //PB7輸出模式
//IO操作函數	 
#define IIC1_SCL    PBout(6) //SCL
#define IIC1_SDA    PBout(7) //SDA	 
#define READ1_SDA   PBin(7)  //輸入SDA 

#define OLED_CMD  0	
#define OLED_DATA 1

//IIC所有操作函數
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//發送IIC開始信號
void IIC_Stop(void);	  			//發送IIC停止信號
void IIC_Send_Byte(u8 txd);			//IIC發送一個字節
u8 IIC_Read_Byte(unsigned char ack);//IIC讀取一個字節
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信號
void IIC_Ack(void);					//IIC發送ACK信號
void IIC_NAck(void);				//IIC不發送ACK信號

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

void IIC1_Init(void);                //初始化IIC的IO口				 
void IIC1_Start(void);				//發送IIC開始信號
void IIC1_Stop(void);	  			//發送IIC停止信號
unsigned char IIC1_Send_Byte(u8 txd);			//IIC發送一個字節
u8 IIC1_Read_Byte(unsigned char ack);//IIC讀取一個字節
u8 IIC1_Wait_Ack(void); 				//IIC等待ACK信號
void IIC1_Ack(void);					//IIC發送ACK信號
void IIC1_NAck(void);				//IIC不發送ACK信號

void IIC1_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC1_Read_One_Byte(u8 daddr,u8 addr);	 


void Write_IIC_Command(unsigned char c);
void Write_IIC_Data(unsigned char c);
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Clear(void);
void OLED_All(void);
void OLED_Init(void);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowChar8_16(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowChar11_16(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowChar24_32(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr);

#endif
















