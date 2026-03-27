#ifndef __SYS_H
#define __SYS_H	 
#include "stm32f4xx.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//系統時鐘初始化	
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/2
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改說明
//無
////////////////////////////////////////////////////////////////////////////////// 


//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_OS		0		//定義系統文件夾是否支持UCOS
																	    
	 
//位帶操作,實現51類似的GPIO控制功能
//具體實現思想,參考<<CM3權威指南>>第五章(87頁~92頁).M4同M3類似,只是寄存器地址變了.
//IO口操作宏定義
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO口操作,只對單一的IO口!
//確保n的值小於16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //輸出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //輸入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //輸出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //輸入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //輸出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //輸入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //輸出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //輸入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //輸出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //輸入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //輸出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //輸入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //輸出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //輸入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //輸出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //輸入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //輸出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //輸入

//以下為彙編函數
void WFI_SET(void);		//執行WFI指令
void INTX_DISABLE(void);//關閉所有中斷
void INTX_ENABLE(void);	//開啟所有中斷
void MSR_MSP(u32 addr);	//設置堆棧地址 
#endif











