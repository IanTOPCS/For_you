#ifndef __USMART_H
#define __USMART_H	  		  
#include "usmart_str.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32開發板	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com 
//版本：V3.1
//版權所有，盜版必究。
//Copyright(C) 正點原子 2011-2021
//All rights reserved
//********************************************************************************
//升級說明
//V1.4
//增加了對參數為string類型的函數的支持.適用範圍大大提高.
//優化了內存佔用,靜態內存佔用為79個字節@10個參數.動態適應數字及字符串長度
//V2.0 
//1,修改了list指令,打印函數的完整表達式.
//2,增加了id指令,打印每個函數的入口地址.
//3,修改了參數匹配,支持函數參數的調用(輸入入口地址).
//4,增加了函數名長度宏定義.	
//V2.1 20110707		 
//1,增加dec,hex兩個指令,用於設置參數顯示進制,及執行進制轉換.
//注:當dec,hex不帶參數的時候,即設定顯示參數進制.當後跟參數的時候,即執行進制轉換.
//如:"dec 0XFF" 則會將0XFF轉為255,由串口返回.
//如:"hex 100" 	則會將100轉為0X64,由串口返回
//2,新增usmart_get_cmdname函數,用於獲取指令名字.
//V2.2 20110726	
//1,修正了void類型參數的參數統計錯誤.
//2,修改數據顯示格式默認為16進制.
//V2.3 20110815
//1,去掉了函數名後必須跟"("的限制.
//2,修正了字符串參數中不能有"("的bug.
//3,修改了函數默認顯示參數格式的修改方式. 
//V2.4 20110905
//1,修改了usmart_get_cmdname函數,增加最大參數長度限制.避免了輸入錯誤參數時的死機現象.
//2,增加USMART_ENTIM2_SCAN宏定義,用於配置是否使用TIM2定時執行scan函數.
//V2.5 20110930
//1,修改usmart_init函數為void usmart_init(u8 sysclk),可以根據系統頻率自動設定掃瞄時間.(固定100ms)
//2,去掉了usmart_init函數中的uart_init函數,串口初始化必須在外部初始化,方便用戶自行管理.
//V2.6 20111009
//1,增加了read_addr和write_addr兩個函數.可以利用這兩個函數讀寫內部任意地址(必須是有效地址).更加方便調試.
//2,read_addr和write_addr兩個函數可以通過設置USMART_USE_WRFUNS為來使能和關閉.
//3,修改了usmart_strcmp,使其規範化.			  
//V2.7 20111024
//1,修正了返回值16進制顯示時不換行的bug.
//2,增加了函數是否有返回值的判斷,如果沒有返回值,則不會顯示.有返回值時才顯示其返回值.
//V2.8 20111116
//1,修正了list等不帶參數的指令發送後可能導致死機的bug.
//V2.9 20120917
//1,修改了形如：void*xxx(void)類型函數不能識別的bug。
//V3.0 20130425
//1,新增了字符串參數對轉義符的支持。
//V3.1 20131120
//1,增加runtime系統指令,可以用於統計函數執行時間.
//用法:
//發送:runtime 1 ,則開啟函數執行時間統計功能
//發送:runtime 0 ,則關閉函數執行時間統計功能
///runtime統計功能,必須設置:USMART_ENTIMX_SCAN 為1,才可以使用!!
/////////////////////////////////////////////////////////////////////////////////////
//USMART資源佔用情況@MDK 3.80A@2.0版本：
//FLASH:4K~K字節(通過USMART_USE_HELP和USMART_USE_WRFUNS設置)
//SRAM:72字節(最少的情況下)
//SRAM計算公式:   SRAM=PARM_LEN+72-4  其中PARM_LEN必須大於等於4.
//應該保證堆棧不小於100個字節.
////////////////////////////////////////////用戶配置參數////////////////////////////////////////////////////	  
#define MAX_FNAME_LEN 		30	//函數名最大長度，應該設置為不小於最長函數名的長度。											   
#define MAX_PARM 			10	//最大為10個參數 ,修改此參數,必須修改usmart_exe與之對應.
#define PARM_LEN 			200	//所有參數之和的長度不超過PARM_LEN個字節,注意串口接收部分要與之對應(不小於PARM_LEN)


#define USMART_ENTIMX_SCAN 	1	//使用TIM的定時中斷來掃瞄SCAN函數,如果設置為0,需要自己實現隔一段時間掃瞄一次scan函數.
								//注意:如果要用runtime統計功能,必須設置USMART_ENTIMX_SCAN為1!!!!
								
#define USMART_USE_HELP		1	//使用幫助，該值設為0，可以節省近700個字節，但是將導致無法顯示幫助信息。
#define USMART_USE_WRFUNS	1	//使用讀寫函數,使能這裡,可以讀取任何地址的值,還可以寫寄存器的值.
///////////////////////////////////////////////END///////////////////////////////////////////////////////////

#define USMART_OK 			0  //無錯誤
#define USMART_FUNCERR 		1  //函數錯誤
#define USMART_PARMERR 		2  //參數錯誤
#define USMART_PARMOVER 	3  //參數溢出
#define USMART_NOFUNCFIND 	4  //未找到匹配函數

#define SP_TYPE_DEC      	0  //10進制參數顯示
#define SP_TYPE_HEX       	1  //16進制參數顯示


 //函數名列表	 
struct _m_usmart_nametab
{
	void* func;			//函數指針
	const u8* name;		//函數名(查找串)	 
};
//usmart控制管理器
struct _m_usmart_dev
{
	struct _m_usmart_nametab *funs;	//函數名指針

	void (*init)(u8);				//初始化
	u8 (*cmd_rec)(u8*str);			//識別函數名及參數
	void (*exe)(void); 				//執行 
	void (*scan)(void);             //掃瞄
	u8 fnum; 				  		//函數數量
	u8 pnum;                        //參數數量
	u8 id;							//函數id
	u8 sptype;						//參數顯示類型(非字符串參數):0,10進制;1,16進制;
	u16 parmtype;					//參數的類型
	u8  plentbl[MAX_PARM];  		//每個參數的長度暫存表
	u8  parm[PARM_LEN];  			//函數的參數
	u8 runtimeflag;					//0,不統計函數執行時間;1,統計函數執行時間,注意:此功能必須在USMART_ENTIMX_SCAN使能的時候,才有用
	u32 runtime;					//運行時間,單位:0.1ms,最大延時時間為定時器CNT值的2倍*0.1ms
};
extern struct _m_usmart_nametab usmart_nametab[];	//在usmart_config.c裡面定義
extern struct _m_usmart_dev usmart_dev;				//在usmart_config.c裡面定義


void usmart_init(u8 sysclk);//初始化
u8 usmart_cmd_rec(u8*str);	//識別
void usmart_exe(void);		//執行
void usmart_scan(void);     //掃瞄
u32 read_addr(u32 addr);	//讀取指定地址的值
void write_addr(u32 addr,u32 val);//在指定地址寫入指定的值
u32 usmart_get_runtime(void);	//獲取運行時間
void usmart_reset_runtime(void);//復位運行時間

#endif






























