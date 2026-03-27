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
#endif
















