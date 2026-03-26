#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "sys.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//電容觸摸屏-IIC 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.1
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
//********************************************************************************
//修改說明
//V1.1 20140721
//1,修改CT_IIC_Read_Byte函數,讀數據更快.
//2,修改CT_IIC_Wait_Ack函數,以支持MDK的-O2優化.
////////////////////////////////////////////////////////////////////////////////// 	

//IO方向設置
#define CT_SDA_IN()  {GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=0<<2*11;}	//PF11輸入模式
#define CT_SDA_OUT() {GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=1<<2*11;} 	//PF11輸出模式
//IO操作函數	 
#define CT_IIC_SCL    PBout(0) 	//SCL
#define CT_IIC_SDA    PFout(11) //SDA	 
#define CT_READ_SDA   PFin(11)  //輸入SDA 
 

//IIC所有操作函數
void CT_IIC_Init(void);                	//初始化IIC的IO口				 
void CT_IIC_Start(void);				//發送IIC開始信號
void CT_IIC_Stop(void);	  				//發送IIC停止信號
void CT_IIC_Send_Byte(u8 txd);			//IIC發送一個字節
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC讀取一個字節
u8 CT_IIC_Wait_Ack(void); 				//IIC等待ACK信號
void CT_IIC_Ack(void);					//IIC發送ACK信號
void CT_IIC_NAck(void);					//IIC不發送ACK信號

#endif







