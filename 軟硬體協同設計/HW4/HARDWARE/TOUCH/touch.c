#include "touch.h" 
#include "lcd.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "24cxx.h" 
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

_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//默認為touchtype=0的數據.
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;
 	 			    					   
//SPI寫數據
//向觸摸屏IC寫入1byte數據    
//num:要寫入的數據
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN=1;  
		else TDIN=0;   
		num<<=1;    
		TCLK=0; 
		delay_us(1);
		TCLK=1;		//上升沿有效	        
	}		 			    
} 		 
//SPI讀數據 
//從觸摸屏IC讀取adc值
//CMD:指令
//返回值:讀到的數據	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;		//先拉低時鐘 	 
	TDIN=0; 	//拉低數據線
	TCS=0; 		//選中觸摸屏IC
	TP_Write_Byte(CMD);//發送命令字
	delay_us(6);//ADS7846的轉換時間最長為6us
	TCLK=0; 	     	    
	delay_us(1);    	   
	TCLK=1;		//給1個時鐘，清除BUSY
	delay_us(1);    
	TCLK=0; 	     	    
	for(count=0;count<16;count++)//讀出16位數據,只有高12位有效 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//下降沿有效  	    	   
		delay_us(1);    
 		TCLK=1;
 		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//只有高12位有效.
	TCS=1;		//釋放片選	 
	return(Num);   
}
//讀取一個坐標值(x或者y)
//連續讀取READ_TIMES次數據,對這些數據升序排列,
//然後去掉最低和最高LOST_VAL個數,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:讀到的數據
#define READ_TIMES 5 	//讀取次數
#define LOST_VAL 1	  	//丟棄值
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//讀取x,y坐標
//最小值不能少於100.
//x,y:讀取到的坐標值
//返回值:0,失敗;1,成功。
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//讀數失敗
	*x=xtemp;
	*y=ytemp;
	return 1;//讀數成功
}
//連續2次讀取觸摸屏IC,且這兩次的偏差不能超過
//ERR_RANGE,滿足條件,則認為讀數正確,否則讀數錯誤.	   
//該函數能大大提高準確度
//x,y:讀取到的坐標值
//返回值:0,失敗;1,成功。
#define ERR_RANGE 50 //誤差範圍 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前後兩次採樣在+-50內
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}  
//////////////////////////////////////////////////////////////////////////////////		  
//與LCD部分有關的函數  
//畫一個觸摸點
//用來校準用的
//x,y:坐標
//color:顏色
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color)
{
	POINT_COLOR=color;
	LCD_DrawLine(x-12,y,x+13,y);//橫線
	LCD_DrawLine(x,y-12,x,y+13);//豎線
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);
	LCD_Draw_Circle(x,y,6);//畫中心圈
}	  
//畫一個大點(2*2的點)		   
//x,y:坐標
//color:顏色
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	POINT_COLOR=color;
	LCD_DrawPoint(x,y);//中心點 
	LCD_DrawPoint(x+1,y);
	LCD_DrawPoint(x,y+1);
	LCD_DrawPoint(x+1,y+1);	 	  	
}						  
//////////////////////////////////////////////////////////////////////////////////		  
//觸摸按鍵掃瞄
//tp:0,屏幕坐標;1,物理坐標(校準等特殊場合用)
//返回值:當前觸屏狀態.
//0,觸屏無觸摸;1,觸屏有觸摸
u8 TP_Scan(u8 tp)
{			   
	if(PEN==0)//有按鍵按下
	{
		if(tp)TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//讀取物理坐標
		else if(TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]))//讀取屏幕坐標
		{
	 		tp_dev.x[0]=tp_dev.xfac*tp_dev.x[0]+tp_dev.xoff;//將結果轉換為屏幕坐標
			tp_dev.y[0]=tp_dev.yfac*tp_dev.y[0]+tp_dev.yoff;  
	 	} 
		if((tp_dev.sta&TP_PRES_DOWN)==0)//之前沒有被按下
		{		 
			tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//按鍵按下  
			tp_dev.x[4]=tp_dev.x[0];//記錄第一次按下時的坐標
			tp_dev.y[4]=tp_dev.y[0];  	   			 
		}			   
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);//標記按鍵鬆開	
		}else//之前就沒有被按下
		{
			tp_dev.x[4]=0;
			tp_dev.y[4]=0;
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
		}	    
	}
	return tp_dev.sta&TP_PRES_DOWN;//返回當前的觸屏狀態
}	  
//////////////////////////////////////////////////////////////////////////	 
//保存在EEPROM裡面的地址區間基址,佔用13個字節(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
#define SAVE_ADDR_BASE 40
//保存校準參數										    
void TP_Save_Adjdata(void)
{
	s32 temp;			 
	//保存校正結果!		   							  
	temp=tp_dev.xfac*100000000;//保存x校正因素      
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);   
	temp=tp_dev.yfac*100000000;//保存y校正因素    
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);
	//保存x偏移量
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);		    
	//保存y偏移量
	AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);	
	//保存觸屏類型
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);	
	temp=0X0A;//標記校準過了
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp); 
}
//得到保存在EEPROM裡面的校準值
//返回值：1，成功獲取數據
//        0，獲取失敗，要重新校準
u8 TP_Get_Adjdata(void)
{					  
	s32 tempfac;
	tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);//讀取標記字,看是否校準過！ 		 
	if(tempfac==0X0A)//觸摸屏已經校準過了			   
	{    												 
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);		   
		tp_dev.xfac=(float)tempfac/100000000;//得到x校準參數
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);			          
		tp_dev.yfac=(float)tempfac/100000000;//得到y校準參數
	    //得到x偏移量
		tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);			   	  
 	    //得到y偏移量
		tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);				 	  
 		tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);//讀取觸屏類型標記
		if(tp_dev.touchtype)//X,Y方向與屏幕相反
		{
			CMD_RDX=0X90;
			CMD_RDY=0XD0;	 
		}else				   //X,Y方向與屏幕相同
		{
			CMD_RDX=0XD0;
			CMD_RDY=0X90;	 
		}		 
		return 1;	 
	}
	return 0;
}	 
//提示字符串
u8* const TP_REMIND_MSG_TBL="Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";
 					  
//提示校準結果(各個參數)
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
{	  
	POINT_COLOR=RED;
	LCD_ShowString(40,160,lcddev.width,lcddev.height,16,"x1:");
 	LCD_ShowString(40+80,160,lcddev.width,lcddev.height,16,"y1:");
 	LCD_ShowString(40,180,lcddev.width,lcddev.height,16,"x2:");
 	LCD_ShowString(40+80,180,lcddev.width,lcddev.height,16,"y2:");
	LCD_ShowString(40,200,lcddev.width,lcddev.height,16,"x3:");
 	LCD_ShowString(40+80,200,lcddev.width,lcddev.height,16,"y3:");
	LCD_ShowString(40,220,lcddev.width,lcddev.height,16,"x4:");
 	LCD_ShowString(40+80,220,lcddev.width,lcddev.height,16,"y4:");  
 	LCD_ShowString(40,240,lcddev.width,lcddev.height,16,"fac is:");     
	LCD_ShowNum(40+24,160,x0,4,16);		//顯示數值
	LCD_ShowNum(40+24+80,160,y0,4,16);	//顯示數值
	LCD_ShowNum(40+24,180,x1,4,16);		//顯示數值
	LCD_ShowNum(40+24+80,180,y1,4,16);	//顯示數值
	LCD_ShowNum(40+24,200,x2,4,16);		//顯示數值
	LCD_ShowNum(40+24+80,200,y2,4,16);	//顯示數值
	LCD_ShowNum(40+24,220,x3,4,16);		//顯示數值
	LCD_ShowNum(40+24+80,220,y3,4,16);	//顯示數值
 	LCD_ShowNum(40+56,240,fac,3,16); 	//顯示數值,該數值必須在95~105範圍之內.

}
		 
//觸摸屏校準代碼
//得到四個校準參數
void TP_Adjust(void)
{								 
	u16 pos_temp[4][2];//坐標緩存值
	u8  cnt=0;	
	u16 d1,d2;
	u32 tem1,tem2;
	double fac; 	
	u16 outtime=0;
 	cnt=0;				
	POINT_COLOR=BLUE;
	BACK_COLOR =WHITE;
	LCD_Clear(WHITE);//清屏   
	POINT_COLOR=RED;//紅色 
	LCD_Clear(WHITE);//清屏 	   
	POINT_COLOR=BLACK;
	LCD_ShowString(40,40,160,100,16,(u8*)TP_REMIND_MSG_TBL);//顯示提示信息
	TP_Drow_Touch_Point(20,20,RED);//畫點1 
	tp_dev.sta=0;//消除觸發信號 
	tp_dev.xfac=0;//xfac用來標記是否校準過,所以校準之前必須清掉!以免錯誤	 
	while(1)//如果連續10秒鐘沒有按下,則自動退出
	{
		tp_dev.scan(1);//掃瞄物理坐標
		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//按鍵按下了一次(此時按鍵鬆開了.)
		{	
			outtime=0;		
			tp_dev.sta&=~(1<<6);//標記按鍵已經被處理過了.
						   			   
			pos_temp[cnt][0]=tp_dev.x[0];
			pos_temp[cnt][1]=tp_dev.y[0];
			cnt++;	  
			switch(cnt)
			{			   
				case 1:						 
					TP_Drow_Touch_Point(20,20,WHITE);				//清除點1 
					TP_Drow_Touch_Point(lcddev.width-20,20,RED);	//畫點2
					break;
				case 2:
 					TP_Drow_Touch_Point(lcddev.width-20,20,WHITE);	//清除點2
					TP_Drow_Touch_Point(20,lcddev.height-20,RED);	//畫點3
					break;
				case 3:
 					TP_Drow_Touch_Point(20,lcddev.height-20,WHITE);			//清除點3
 					TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,RED);	//畫點4
					break;
				case 4:	 //全部四個點已經得到
	    		    //對邊相等
					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,2的距離
					
					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到3,4的距離
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05||d1==0||d2==0)//不合格
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//清除點4
   	 					TP_Drow_Touch_Point(20,20,RED);								//畫點1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//顯示數據   
 						continue;
					}
					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,3的距離
					
					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,4的距離
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//清除點4
   	 					TP_Drow_Touch_Point(20,20,RED);								//畫點1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//顯示數據   
						continue;
					}//正確了
								   
					//對角線相等
					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,4的距離
	
					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,3的距離
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//清除點4
   	 					TP_Drow_Touch_Point(20,20,RED);								//畫點1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//顯示數據   
						continue;
					}//正確了
					//計算結果
					tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//得到xfac		 
					tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//得到xoff
						  
					tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//得到yfac
					tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//得到yoff  
					if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)//觸屏和預設的相反了.
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//清除點4
   	 					TP_Drow_Touch_Point(20,20,RED);								//畫點1
						LCD_ShowString(40,26,lcddev.width,lcddev.height,16,"TP Need readjust!");
						tp_dev.touchtype=!tp_dev.touchtype;//修改觸屏類型.
						if(tp_dev.touchtype)//X,Y方向與屏幕相反
						{
							CMD_RDX=0X90;
							CMD_RDY=0XD0;	 
						}else				   //X,Y方向與屏幕相同
						{
							CMD_RDX=0XD0;
							CMD_RDY=0X90;	 
						}			    
						continue;
					}		
					POINT_COLOR=BLUE;
					LCD_Clear(WHITE);//清屏
					LCD_ShowString(35,110,lcddev.width,lcddev.height,16,"Touch Screen Adjust OK!");//校正完成
					delay_ms(1000);
					TP_Save_Adjdata();  
 					LCD_Clear(WHITE);//清屏   
					return;//校正完成				 
			}
		}
		delay_ms(10);
		outtime++;
		if(outtime>1000)
		{
			TP_Get_Adjdata();
			break;
	 	} 
 	}
}	
//觸摸屏初始化  		    
//返回值:0,沒有進行校準
//       1,進行過校準
u8 TP_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
	
	if(lcddev.id==0X5510)		//電容觸摸屏
	{
		if(GT9147_Init()==0)	//是GT9147
		{ 
			tp_dev.scan=GT9147_Scan;	//掃瞄函數指向GT9147觸摸屏掃瞄
		}else
		{
			OTT2001A_Init();
			tp_dev.scan=OTT2001A_Scan;	//掃瞄函數指向OTT2001A觸摸屏掃瞄
		}
		tp_dev.touchtype|=0X80;	//電容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//橫屏還是豎屏 
		return 0;
	}else if(lcddev.id==0X1963)
	{
		FT5206_Init();
		tp_dev.scan=FT5206_Scan;		//掃瞄函數指向GT9147觸摸屏掃瞄		
		tp_dev.touchtype|=0X80;			//電容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//橫屏還是豎屏 
		return 0;
	}else
	{
		
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOB,C,F時鐘

    //GPIOB1,2初始化設置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;//PB1/PB2 設置為上拉輸入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//輸入模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽輸出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0設置為推挽輸出
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PC13設置為推挽輸出
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
	  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化	
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PF11設置推挽輸出
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
	  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化			
		
   
		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//第一次讀取初始化	 
		AT24CXX_Init();		//初始化24CXX
		if(TP_Get_Adjdata())return 0;//已經校準
		else			   //未校準?
		{ 										    
			LCD_Clear(WHITE);//清屏
			TP_Adjust();  	//屏幕校準 
			TP_Save_Adjdata();	 
		}			
		TP_Get_Adjdata();	
	}
	return 1; 									 
}
