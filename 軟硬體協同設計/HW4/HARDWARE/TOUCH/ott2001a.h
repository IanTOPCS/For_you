#ifndef __OTT2001A_H
#define __OTT2001A_H	
#include "sys.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//4.3寸電容觸摸屏-OTT2001A 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


//IO操作函數	 
#define OTT_RST    		PCout(13)	//OTT2001A復位引腳
#define OTT_INT    		PBin(1)		//OTT2001A中斷引腳	
  
//通過OTT_SET_REG指令,可以查詢到這個信息 
//注意,這裡的X,Y和屏幕的坐標系剛好是反的.
#define OTT_MAX_X 		2700	 	//TP X方向的最大值(豎方向)
#define OTT_MAX_Y 		1500    	//TP Y方向的最大值(橫方向)

//縮放因子
#define OTT_SCAL_X		0.2963		//屏幕的 縱坐標/OTT_MAX_X		
#define OTT_SCAL_Y		0.32		//屏幕的 橫坐標/OTT_MAX_Y		
 
//I2C讀寫命令	
#define OTT_CMD_WR 		0XB2     	//寫命令
#define OTT_CMD_RD 		0XB3		//讀命令
 
//寄存器地址
#define OTT_GSTID_REG 	0X0000   	//OTT2001A當前檢測到的觸摸情況
#define OTT_TP1_REG 	0X0100  	//第一個觸摸點數據地址
#define OTT_TP2_REG 	0X0500		//第二個觸摸點數據地址
#define OTT_TP3_REG 	0X1000		//第三個觸摸點數據地址
#define OTT_TP4_REG 	0X1400		//第四個觸摸點數據地址
#define OTT_TP5_REG 	0X1800		//第五個觸摸點數據地址  
#define OTT_SET_REG   	0X0900   	//分辨率設置寄存器地址
#define OTT_CTRL_REG  	0X0D00   	//傳感器控制(開/關)  

#define OTT_MAX_TOUCH  5    		//電容屏支持的點數,固定為5點
 	

u8 OTT2001A_WR_Reg(u16 reg,u8 *buf,u8 len);		//寫寄存器(實際無用)
void OTT2001A_RD_Reg(u16 reg,u8 *buf,u8 len);	//讀寄存器
void OTT2001A_SensorControl(u8 cmd);//傳感器打開/關閉操作
u8 OTT2001A_Init(void); 			//4.3電容觸摸屏始化函數
u8 OTT2001A_Scan(u8 mode);			//電容觸摸屏掃瞄函數

#endif













