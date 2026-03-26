#ifndef __FT5206_H
#define __FT5206_H	
#include "sys.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32開發板
//7寸電容觸摸屏-FT5206 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/11/30
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
 


//與電容觸摸屏連接的芯片引腳(未包含IIC引腳) 
//IO操作函數	 
#define FT_RST    				PCout(13)	//FT5206復位引腳
#define FT_INT    				PBin(1)		//FT5206中斷引腳	

//I2C讀寫命令	
#define FT_CMD_WR 				0X70    	//寫命令
#define FT_CMD_RD 				0X71		//讀命令
  
//FT5206 部分寄存器定義 
#define FT_DEVIDE_MODE 			0x00   		//FT5206模式控制寄存器
#define FT_REG_NUM_FINGER       0x02		//觸摸狀態寄存器

#define FT_TP1_REG 				0X03	  	//第一個觸摸點數據地址
#define FT_TP2_REG 				0X09		//第二個觸摸點數據地址
#define FT_TP3_REG 				0X0F		//第三個觸摸點數據地址
#define FT_TP4_REG 				0X15		//第四個觸摸點數據地址
#define FT_TP5_REG 				0X1B		//第五個觸摸點數據地址  
 

#define	FT_ID_G_LIB_VERSION		0xA1		//版本		
#define FT_ID_G_MODE 			0xA4   		//FT5206中斷模式控制寄存器
#define FT_ID_G_THGROUP			0x80   		//觸摸有效值設置寄存器
#define FT_ID_G_PERIODACTIVE	0x88   		//激活狀態週期設置寄存器


u8 FT5206_WR_Reg(u16 reg,u8 *buf,u8 len);
void FT5206_RD_Reg(u16 reg,u8 *buf,u8 len);
u8 FT5206_Init(void);
u8 FT5206_Scan(u8 mode);

#endif

















