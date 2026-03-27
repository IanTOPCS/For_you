#include "gt9147.h"
#include "touch.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 
#include "lcd.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//4.3寸電容觸摸屏-GT9147 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//GT9147配置參數表
//第一個字節為版本號(0X60),必須保證新的版本號大於等於GT9147內部
//flash原有版本號,才會更新配置.
const u8 GT9147_CFG_TBL[]=
{ 
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  
//發送GT9147配置參數
//mode:0,參數不保存到flash
//     1,參數保存到flash
u8 GT9147_Send_Cfg(u8 mode)
{
	u8 buf[2];
	u8 i=0;
	buf[0]=0;
	buf[1]=mode;	//是否寫入到GT9147 FLASH?  即是否掉電保存
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//計算校驗和
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(u8*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//發送寄存器配置
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//寫入校驗和,和配置更新標記
	return 0;
} 
//向GT9147寫入一次數據
//reg:起始寄存器地址
//buf:數據緩緩存區
//len:寫數據長度
//返回值:0,成功;1,失敗.
u8 GT9147_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//發送寫命令 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//發送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//發送低8位地址
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//發數據
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//產生一個停止條件	    
	return ret; 
}
//從GT9147讀出一次數據
//reg:起始寄存器地址
//buf:數據緩緩存區
//len:讀數據長度			  
void GT9147_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //發送寫命令 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//發送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//發送低8位地址
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //發送讀命令		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //發數據	  
	} 
    CT_IIC_Stop();//產生一個停止條件    
} 
//初始化GT9147觸摸屏
//返回值:0,初始化成功;1,初始化失敗 
u8 GT9147_Init(void)
{
	u8 temp[5]; 
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOB,C時鐘

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;//PB1設置為上拉輸入
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//輸入模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽輸出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//PC13設置為推挽輸出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化	
	
	CT_IIC_Init();      	//初始化電容屏的I2C總線  
	GT_RST=0;				//復位
	delay_ms(10);
 	GT_RST=1;				//釋放復位		    
	delay_ms(10); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PB1設置為浮空輸入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化	
	
	delay_ms(100);  
	GT9147_RD_Reg(GT_PID_REG,temp,4);//讀取產品ID
	temp[4]=0;
	printf("CTP ID:%s\r\n",temp);	//打印ID
	if(strcmp((char*)temp,"9147")==0)//ID==9147
	{
		temp[0]=0X02;			
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//軟復位GT9147
		GT9147_RD_Reg(GT_CFGS_REG,temp,1);//讀取GT_CFGS_REG寄存器
		if(temp[0]<0X60)//默認版本比較低,需要更新flash配置
		{
			printf("Default Ver:%d\r\n",temp[0]);
			GT9147_Send_Cfg(1);//更新並保存配置
		}
		delay_ms(10);
		temp[0]=0X00;	 
		GT9147_WR_Reg(GT_CTRL_REG,temp,1);//結束復位   
		return 0;
	} 
	return 1;
}
const u16 GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//掃瞄觸摸屏(採用查詢方式)
//mode:0,正常掃瞄.
//返回值:當前觸屏狀態.
//0,觸屏無觸摸;1,觸屏有觸摸
u8 GT9147_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
 	static u8 t=0;//控制查詢間隔,從而降低CPU佔用率   
	t++;
	if((t%10)==0||t<10)//空閒時,每進入10次CTP_Scan函數才檢測1次,從而節省CPU使用率
	{
		GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//讀取觸摸點的狀態  
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//清標誌 		
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//將點的個數轉換為1的位數,匹配tp_dev.sta定義 
			tempsta=tp_dev.sta;			//保存當前的tp_dev.sta值
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//保存觸點0的數據
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//觸摸有效?
				{
					GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,4);	//讀取XY坐標值
					if(tp_dev.touchtype&0X01)//橫屏
					{
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.x[i]=800-(((u16)buf[3]<<8)+buf[2]);
					}else
					{
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
					}  
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//非法數據(坐標超出了)
			{ 
				if((mode&0XF)>1)		//有其他點有數據,則復第二個觸點的數據到第一個觸點.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//觸發一次,則會最少連續監測10次,從而提高命中率
				}else					//非法數據,則忽略此次數據(還原原來的)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//恢復tp_dev.sta
				}
			}else t=0;					//觸發一次,則會最少連續監測10次,從而提高命中率
		}
	}
	if((mode&0X8F)==0X80)//無觸摸點按下
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);	//標記按鍵鬆開
		}else						//之前就沒有被按下
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//清除點有效標記	
		}	 
	} 	
	if(t>240)t=10;//重新從10開始計數
	return res;
}
 



























