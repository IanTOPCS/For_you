#ifndef __GT9147_H
#define __GT9147_H	
#include "sys.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//4.3寸電容觸摸屏-GT9147 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//IO操作函數	 
#define GT_RST    		PCout(13)	//GT9147復位引腳
#define GT_INT    		PBin(1)		//GT9147中斷引腳	
   	
 
//I2C讀寫命令	
#define GT_CMD_WR 		0X28     	//寫命令
#define GT_CMD_RD 		0X29		//讀命令
  
//GT9147 部分寄存器定義 
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校驗和寄存器
#define GT_PID_REG 		0X8140   	//GT9147產品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147當前檢測到的觸摸情況
#define GT_TP1_REG 		0X8150  	//第一個觸摸點數據地址
#define GT_TP2_REG 		0X8158		//第二個觸摸點數據地址
#define GT_TP3_REG 		0X8160		//第三個觸摸點數據地址
#define GT_TP4_REG 		0X8168		//第四個觸摸點數據地址
#define GT_TP5_REG 		0X8170		//第五個觸摸點數據地址  
 
 
u8 GT9147_Send_Cfg(u8 mode);
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len);
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len); 
u8 GT9147_Init(void);
u8 GT9147_Scan(u8 mode); 
#endif













