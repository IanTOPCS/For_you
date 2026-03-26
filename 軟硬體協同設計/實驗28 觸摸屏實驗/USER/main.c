#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "touch.h" 
//ALIENTEK 探索者STM32F407開發板 實驗28
//觸摸屏實驗   --庫函數版本
//技術支持：www.openedv.com
//淘寶店舖：http://eboard.taobao.com  
//廣州市星翼電子科技有限公司  
//作者：正點原子 @ALIENTEK

//清空屏幕並在右上角顯示"RST"
void Load_Drow_Dialog(void)
{
	LCD_Clear(BLACK);//清屏   
 	POINT_COLOR=BLUE;//設置字體為藍色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//顯示清屏區域
  	POINT_COLOR=RED;//設置畫筆藍色 
}
////////////////////////////////////////////////////////////////////////////////
//電容觸摸屏專有部分
//畫水平線
//x0,y0:坐標
//len:線長度
//color:顏色
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//畫實心圓
//x0,y0:坐標
//r:半徑
//color:顏色
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
//兩個數之差的絕對值 
//x1,x2：需取差值的兩個數
//返回值：|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//畫一條粗線
//(x1,y1),(x2,y2):線條的起始坐標
//size：線條的粗細程度
//color：線條的顏色
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //計算坐標增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //設置單步方向 
	else if(delta_x==0)incx=0;//垂直線 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平線 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //選取基本增量坐標軸 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//畫線輸出 
	{  
		gui_fill_circle(uRow,uCol,size,color);//畫點 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   
////////////////////////////////////////////////////////////////////////////////
 //5個觸控點的顏色(電容觸摸屏用)												 
const u16 POINT_COLOR_TBL[OTT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};  
//電阻觸摸屏測試函數
void rtp_test(void)
{
	u8 key;
	u8 i=0;
	while(1)
	{
	 	key=KEY_Scan(0);
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//觸摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Drow_Dialog();//清除
				else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//畫圖	  			   
			}
		}else delay_ms(10);	//沒有按鍵按下的時候 	    
		if(key==KEY0_PRES)	//KEY0按下,則執行校準程序
		{
			LCD_Clear(WHITE);	//清屏
		    TP_Adjust();  		//屏幕校準 
			TP_Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i%20==0)LED0=!LED0;
	}
}
//電容觸摸屏測試函數
void ctp_test(void)
{
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//最後一次的數據 
	while(1)
	{
		tp_dev.scan(0);
		for(t=0;t<OTT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//畫線
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<20)
					{
						Load_Drow_Dialog();//清除
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}
		
		delay_ms(5);i++;
		if(i%20==0)LED0=!LED0;
	}	
}
	
int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//設置系統中斷優先級分組2
	delay_init(168);  //初始化延時函數
	uart_init(115200);		//初始化串口波特率為115200
	
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化 
	KEY_Init(); 				//按鍵初始化  
	tp_dev.init();				//觸摸屏初始化
 	POINT_COLOR=RED;//設置字體為紅色 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"TOUCH TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");
   	if(tp_dev.touchtype!=0XFF)LCD_ShowString(30,130,200,16,16,"Press KEY0 to Adjust");//電阻屏才顯示
	delay_ms(1500);
 	Load_Drow_Dialog();	 	
	
	if(tp_dev.touchtype&0X80)ctp_test();//電容屏測試
	else rtp_test(); 					//電阻屏測試
}
