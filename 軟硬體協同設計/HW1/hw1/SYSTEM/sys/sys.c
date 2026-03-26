#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//系統時鐘初始化	
//包括時鐘設置/中斷管理/GPIO設置等
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


//THUMB指令不支持彙編內聯
//採用如下方法實現執行彙編指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//關閉所有中斷(但是不包括fault和NMI中斷)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//開啟所有中斷
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//設置棧頂地址
//addr:棧頂地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















