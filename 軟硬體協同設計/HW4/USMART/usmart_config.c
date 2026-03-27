#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�Τ�t�m��///////////////////////////////////////////////
//�o�U���n�]�t�ҥΨ쪺��Ʃҥө����Y���(�Τ�ۤv�K�[) 
#include "delay.h"		
#include "sys.h"
#include "lcd.h"
#include "touch.h"
												 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
//��ƦW�C����l��(�Τ�ۤv�K�[)
//�Τ᪽���b�o�̿�J�n���檺��ƦW�Ψ�d���
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//�p�G�ϯ�FŪ�g�ާ@
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
	(void*)TP_Draw_Big_Point, "void TP_Draw_Big_Point(u16 x,u16 y,u16 color)"				  	    
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//��Ʊ���޲z����l��
//�o��U�Ө�����ƪ��W�r
//�o�����`�ƶq
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��Ƽƶq
	0,	  	//�ѼƼƶq
	0,	 	//���ID
	1,		//�Ѽ��������,0,10�i��;1,16�i��
	0,		//�Ѽ�����.bitx:,0,�Ʀr;1,�r�Ŧ�	    
	0,	  	//�C�ӰѼƪ����׼Ȧs��,�ݭnMAX_PARM��0��l��
	0,		//��ƪ��Ѽ�,�ݭnPARM_LEN��0��l��
};   



















