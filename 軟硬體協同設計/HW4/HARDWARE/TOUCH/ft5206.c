#include "ft5206.h"
#include "touch.h"
#include "ctiic.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32開發板
//7寸電容觸摸屏-FT5206 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/11/30
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
 
 
//向FT5206寫入一次數據
//reg:起始寄存器地址
//buf:數據緩緩存區
//len:寫數據長度
//返回值:0,成功;1,失敗.
u8 FT5206_WR_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i;
	u8 ret=0;
	CT_IIC_Start();	 
	CT_IIC_Send_Byte(FT_CMD_WR);	//發送寫命令 	 
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
//從FT5206讀出一次數據
//reg:起始寄存器地址
//buf:數據緩緩存區
//len:讀數據長度			  
void FT5206_RD_Reg(u16 reg,u8 *buf,u8 len)
{
	u8 i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(FT_CMD_WR);   	//發送寫命令 	 
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//發送低8位地址
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(FT_CMD_RD);   	//發送讀命令		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //發數據	  
	} 
    CT_IIC_Stop();//產生一個停止條件     
} 
//初始化FT5206觸摸屏
//返回值:0,初始化成功;1,初始化失敗 
u8 FT5206_Init(void)
{
	u8 temp[2]; 
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
	FT_RST=0;				//復位
	delay_ms(20);
 	FT_RST=1;				//釋放復位		    
	delay_ms(50);  	
	temp[0]=0;
	FT5206_WR_Reg(FT_DEVIDE_MODE,temp,1);	//進入正常操作模式 
	FT5206_WR_Reg(FT_ID_G_MODE,temp,1);		//查詢模式 
	temp[0]=22;								//觸摸有效值，22，越小越靈敏	
	FT5206_WR_Reg(FT_ID_G_THGROUP,temp,1);	//設置觸摸有效值
	temp[0]=12;								//激活週期，不能小於12，最大14
	FT5206_WR_Reg(FT_ID_G_PERIODACTIVE,temp,1); 
	//讀取版本號，參考值：0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION,&temp[0],2);  
	if(temp[0]==0X30&&temp[1]==0X03)//版本:0X3003
	{
		printf("CTP ID:%x\r\n",((u16)temp[0]<<8)+temp[1]);
		return 0;
	} 
	return 1;
}
const u16 FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};
//掃瞄觸摸屏(採用查詢方式)
//mode:0,正常掃瞄.
//返回值:當前觸屏狀態.
//0,觸屏無觸摸;1,觸屏有觸摸
u8 FT5206_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	static u8 t=0;//控制查詢間隔,從而降低CPU佔用率   
	t++;
	if((t%10)==0||t<10)//空閒時,每進入10次CTP_Scan函數才檢測1次,從而節省CPU使用率
	{
		FT5206_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//讀取觸摸點的狀態  
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);//將點的個數轉換為1的位數,匹配tp_dev.sta定義 
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//觸摸有效?
				{
					FT5206_RD_Reg(FT5206_TPX_TBL[i],buf,4);	//讀取XY坐標值 
					if(tp_dev.touchtype&0X01)//橫屏
					{
						tp_dev.y[i]=((u16)(buf[0]&0X0F)<<8)+buf[1];
						tp_dev.x[i]=((u16)(buf[2]&0X0F)<<8)+buf[3];
					}else
					{
						tp_dev.x[i]=480-(((u16)(buf[0]&0X0F)<<8)+buf[1]);
						tp_dev.y[i]=((u16)(buf[2]&0X0F)<<8)+buf[3];
					}  
					if((buf[0]&0XF0)!=0X80)tp_dev.x[i]=tp_dev.y[i]=0;//必須是contact事件，才認為有效
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//讀到的數據都是0,則忽略此次數據
			t=0;		//觸發一次,則會最少連續監測10次,從而提高命中率
		}
	}
	if((mode&0X1F)==0)//無觸摸點按下
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
 



























