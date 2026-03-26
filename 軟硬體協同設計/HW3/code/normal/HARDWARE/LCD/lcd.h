#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
#include "stdlib.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//2.4寸/2.8寸/3.5寸/4.3寸/7寸 TFT液晶驅動	  
//支持驅動IC型號包括:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/1505/B505/C505/NT35310/NT35510/SSD1963等		    
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2010/7/4
//版本：V3.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved	
//********************************************************************************
//V1.2修改說明
//支持了SPFD5408的驅動,另外把液晶ID直接打印成HEX格式.方便查看LCD驅動IC.
//V1.3
//加入了快速IO的支持
//修改了背光控制的極性（適用於V1.8及以後的開發板版本）
//對於1.8版本之前(不包括1.8)的液晶模塊,請修改LCD_Init函數的LCD_LED=1;為LCD_LED=1;
//V1.4
//修改了LCD_ShowChar函數，使用畫點功能畫字符。
//加入了橫豎屏顯示的支持
//V1.5 20110730
//1,修改了B505液晶讀顏色有誤的bug.
//2,修改了快速IO及橫豎屏的設置方式.
//V1.6 20111116
//1,加入對LGDP4535液晶的驅動支持
//V1.7 20120713
//1,增加LCD_RD_DATA函數
//2,增加對ILI9341的支持
//3,增加ILI9325的獨立驅動代碼
//4,增加LCD_Scan_Dir函數(慎重使用)	  
//6,另外修改了部分原來的函數,以適應9341的操作
//V1.8 20120905
//1,加入LCD重要參數設置結構體lcddev
//2,加入LCD_Display_Dir函數,支持在線橫豎屏切換
//V1.9 20120911
//1,新增RM68042驅動（ID:6804），但是6804不支持橫屏顯示！！原因：改變掃瞄方式，
//導致6804坐標設置失效，試過很多方法都不行，暫時無解。
//V2.0 20120924
//在不硬件復位的情況下,ILI9341的ID讀取會被誤讀成9300,修改LCD_Init,將無法識別
//的情況（讀到ID為9300/非法ID）,強制指定驅動IC為ILI9341，執行9341的初始化。
//V2.1 20120930
//修正ILI9325讀顏色的bug。
//V2.2 20121007
//修正LCD_Scan_Dir的bug。
//V2.3 20130120
//新增6804支持橫屏顯示
//V2.4 20131120
//1,新增NT35310（ID:5310）驅動器的支持
//2,新增LCD_Set_Window函數,用於設置窗口,對快速填充,比較有用,但是該函數在橫屏時,不支持6804.
//V2.5 20140211
//1,新增NT35510（ID:5510）驅動器的支持
//V2.6 20140504
//1,新增ASCII 24*24字體的支持(更多字體用戶可以自行添加)  
//2,修改部分函數參數,以支持MDK -O2優化
//3,針對9341/35310/35510,寫時間設置為最快,盡可能的提高速度
//4,去掉了SSD1289的支持,因為1289實在是太慢了,讀週期要1us...簡直奇葩.不適合F4使用
//5,修正68042及C505等IC的讀顏色函數的bug.
//V2.7 20140710
//1,修正LCD_Color_Fill函數的一個bug. 
//2,修正LCD_Scan_Dir函數的一個bug.
//V2.8 20140721
//1,解決MDK使用-O2優化時LCD_ReadPoint函數讀點失效的問題.
//2,修正LCD_Scan_Dir橫屏時設置的掃瞄方式顯示不全的bug.
//V2.9 20141130
//1,新增對SSD1963 LCD的支持.
//2,新增LCD_SSD_BackLightSet函數
//3,取消ILI93XX的Rxx寄存器定義
//V3.0 20150423
//修改SSD1963 LCD屏的驅動參數.
//////////////////////////////////////////////////////////////////////////////////	 

//LCD重要參數集
typedef struct  
{										    
	u16 width;			//LCD 寬度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//橫屏還是豎屏控制：0，豎屏；1，橫屏。	
	u16	wramcmd;		//開始寫gram指令
	u16  setxcmd;		//設置x坐標指令
	u16  setycmd;		//設置y坐標指令 
}_lcd_dev; 	  

//LCD參數
extern _lcd_dev lcddev;	//管理LCD重要參數
//LCD的畫筆顏色和背景色	   
extern u16  POINT_COLOR;//默認紅色    
extern u16  BACK_COLOR; //背景顏色.默認為白色


//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定義---------------- 
#define	LCD_LED PBout(15)  		//LCD背光    		 PB15 	    
//LCD地址結構體
typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作為數據命令區分線 
//注意設置時STM32內部會右移一位對其! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////
	 
//掃瞄方向定義
#define L2R_U2D  0 //從左到右,從上到下
#define L2R_D2U  1 //從左到右,從下到上
#define R2L_U2D  2 //從右到左,從上到下
#define R2L_D2U  3 //從右到左,從下到上

#define U2D_L2R  4 //從上到下,從左到右
#define U2D_R2L  5 //從上到下,從右到左
#define D2U_L2R  6 //從下到上,從左到右
#define D2U_R2L  7 //從下到上,從右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默認的掃瞄方向

//畫筆顏色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕紅色
#define GRAY  			 0X8430 //灰色
//GUI顏色

#define DARKBLUE      	 0X01CF	//深藍色
#define LIGHTBLUE      	 0X7D7C	//淺藍色  
#define GRAYBLUE       	 0X5458 //灰藍色
//以上三色為PANEL的顏色 
 
#define LIGHTGREEN     	 0X841F //淺綠色
//#define LIGHTGRAY        0XEF5B //淺灰色(PANNEL)
#define LGRAY 			 0XC618 //淺灰色(PANNEL),窗體背景色

#define LGRAYBLUE        0XA651 //淺灰藍色(中間層顏色)
#define LBBLUE           0X2B12 //淺棕藍色(選擇條目的反色)
	    															  
void LCD_Init(void);													   	//初始化
void LCD_DisplayOn(void);													//開顯示
void LCD_DisplayOff(void);													//關顯示
void LCD_Clear(u16 Color);	 												//清屏
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//設置光標
void LCD_DrawPoint(u16 x,u16 y);											//畫點
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//快速畫點
u16  LCD_ReadPoint(u16 x,u16 y); 											//讀點 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//畫圓
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//畫線
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//畫矩形
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充單色
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//填充指定顏色
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//顯示一個字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//顯示一個數字
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//顯示 數字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);		//顯示一個字符串,12/16字體

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_SSD_BackLightSet(u8 pwm);							//SSD1963 背光控制
void LCD_Scan_Dir(u8 dir);									//設置屏掃瞄方向
void LCD_Display_Dir(u8 dir);								//設置屏幕顯示方向
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);	//設置窗口					   						   																			 
//LCD分辨率設置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驅動參數設置
#define SSD_HOR_PULSE_WIDTH		1		//水平脈寬
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平後廊

#define SSD_VER_PULSE_WIDTH		1		//垂直脈寬
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下幾個參數，自動計算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif  
	 
	 



