#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//Mini STM32開發板
//串口1初始化		   
//正點原子@ALIENTEK
//技術論壇:www.openedv.csom
//修改日期:2011/6/14
//版本：V1.4
//版權所有，盜版必究。
//Copyright(C) 正點原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改說明 
//支持適應不同頻率下的串口波特率設置.
//加入了對printf的支持
//增加了串口接收命令功能.
//修正了printf第一個字符丟失的bug
//V1.4修改說明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字節數為2的14次方
//3,增加了USART_REC_LEN,用於定義串口最大允許接收的字節數(不大於2的14次方)
//4,修改了EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定義最大接收字節數 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收緩衝,最大USART_REC_LEN個字節.末字節為換行符 
extern u16 USART_RX_STA;         		//接收狀態標記	
//如果想串口中斷接收，請不要註釋以下宏定義
void uart_init(u32 bound);
#endif


