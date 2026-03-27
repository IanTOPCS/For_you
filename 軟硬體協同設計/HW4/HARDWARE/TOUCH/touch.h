#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "sys.h"
#include "ott2001a.h"	    
#include "gt9147.h"	    
#include "ft5206.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//觸摸屏驅動（支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A等） 代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.2
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									   
//********************************************************************************
//修改說明
//V1.1 20140721
//修正MDK在-O2優化時,觸摸屏數據無法讀取的bug.在TP_Write_Byte函數添加一個延時,解決問題.
//V1.2 20141130 
//電容觸摸屏增加FT5206的支持
//////////////////////////////////////////////////////////////////////////////////


#define TP_PRES_DOWN 0x80  //觸屏被按下	  
#define TP_CATH_PRES 0x40  //有按鍵按下了 
#define CT_MAX_TOUCH  5    //電容屏支持的點數,固定為5點

//觸摸屏控制器
typedef struct
{
	u8 (*init)(void);			//初始化觸摸屏控制器
	u8 (*scan)(u8);				//掃瞄觸摸屏.0,屏幕掃瞄;1,物理坐標;	 
	void (*adjust)(void);		//觸摸屏校準 
	u16 x[CT_MAX_TOUCH]; 		//當前坐標
	u16 y[CT_MAX_TOUCH];		//電容屏有最多5組坐標,電阻屏則用x[0],y[0]代表:此次掃瞄時,觸屏的坐標,用
								//x[4],y[4]存儲第一次按下時的坐標. 
	u8  sta;					//筆的狀態 
								//b7:按下1/鬆開0; 
	                            //b6:0,沒有按鍵按下;1,有按鍵按下. 
								//b5:保留
								//b4~b0:電容觸摸屏按下的點數(0,表示未按下,1表示按下)
/////////////////////觸摸屏校準參數(電容屏不需要校準)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//新增的參數,當觸摸屏的左右上下完全顛倒時需要用到.
//b0:0,豎屏(適合左右為X坐標,上下為Y坐標的TP)
//   1,橫屏(適合左右為Y坐標,上下為X坐標的TP) 
//b1~6:保留.
//b7:0,電阻屏
//   1,電容屏 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//觸屏控制器在touch.c裡面定義

//電阻屏芯片連接引腳	   
#define PEN  		PBin(1)  	//T_PEN
#define DOUT 		PBin(2)   	//T_MISO
#define TDIN 		PFout(11)  	//T_MOSI
#define TCLK 		PBout(0)  	//T_SCK
#define TCS  		PCout(13)  	//T_CS  
   
//電阻屏函數
void TP_Write_Byte(u8 num);						//向控制芯片寫入一個數據
u16 TP_Read_AD(u8 CMD);							//讀取AD轉換值
u16 TP_Read_XOY(u8 xy);							//帶濾波的坐標讀取(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//雙方向讀取(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//帶加強濾波的雙方向坐標讀取
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//畫一個坐標校準點
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//畫一個大點
void TP_Save_Adjdata(void);						//保存校準參數
u8 TP_Get_Adjdata(void);						//讀取校準參數
void TP_Adjust(void);							//觸摸屏校準
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//顯示校準信息
//電阻屏/電容屏 共用函數
u8 TP_Scan(u8 tp);								//掃瞄
u8 TP_Init(void);								//初始化
 
#endif

















