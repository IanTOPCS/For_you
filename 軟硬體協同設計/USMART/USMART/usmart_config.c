#include "usmart.h"
#include "usmart_str.h"
////////////////////////////ノめ皌竚跋///////////////////////////////////////////////
//硂璶┮ノㄧ计┮ビ繷ゅン(ノめ睰) 
#include "delay.h"		
#include "sys.h"
#include "lcd.h"
												 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
//ㄧ计﹍て(ノめ睰)
//ノめ钡硂柑块璶磅︽ㄧ计のㄤ琩т﹃
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//狦ㄏ弄糶巨
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",	 
	(void*)LCD_Clear,"void LCD_Clear(u16 Color)",
	(void*)LCD_Fill,"void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)",
	(void*)LCD_DrawLine,"void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)",
	(void*)LCD_DrawRectangle,"void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)",
	(void*)LCD_Draw_Circle,"void Draw_Circle(u16 x0,u16 y0,u8 r)",
	(void*)LCD_ShowNum,"void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)",
	(void*)LCD_ShowString,"void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)",
	(void*)LCD_Fast_DrawPoint,"void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)",
	(void*)LCD_ReadPoint,"u16 LCD_ReadPoint(u16 x,u16 y)",							 
	(void*)LCD_Display_Dir,"void LCD_Display_Dir(u8 dir)",
	(void*)LCD_ShowxNum,"void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)",
	(void*)led_set,"void led_set(u8 sta)",
	(void*)test_fun,"void test_fun(void(*ledset)(u8),u8 sta)",				  	    
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//ㄧ计北恨瞶竟﹍て
//眔北ㄧ计
//眔ㄧ计羆计秖
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//ㄧ计计秖
	0,	  	//把计计秖
	0,	 	//ㄧ计ID
	1,		//把计陪ボ摸,0,10秈;1,16秈
	0,		//把计摸.bitx:,0,计;1,才﹃	    
	0,	  	//–把计既,惠璶MAX_PARM0﹍て
	0,		//ㄧ计把计,惠璶PARM_LEN0﹍て
};   



















