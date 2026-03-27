#include "ctiic.h"
#include "delay.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//電容觸摸屏-IIC 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/7
//版本：V1.1
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
//********************************************************************************
//修改說明
//V1.1 20140721
//1,修改CT_IIC_Read_Byte函數,讀數據更快.
//2,修改CT_IIC_Wait_Ack函數,以支持MDK的-O2優化.
////////////////////////////////////////////////////////////////////////////////// 	

//控制I2C速度的延時
void CT_Delay(void)
{
	delay_us(2);
} 
//電容觸摸芯片IIC接口初始化
void CT_IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;	
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOB,F時鐘
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PB0設置為推挽輸出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽輸出
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PF11設置推挽輸出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//輸出模式
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化	

}
//產生IIC起始信號
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda線輸出
	CT_IIC_SDA=1;	  	  
	CT_IIC_SCL=1;
	delay_us(30);
 	CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL=0;//鉗住I2C總線，準備發送或接收數據 
}	  
//產生IIC停止信號
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda線輸出
	CT_IIC_SCL=1;
	delay_us(30);
	CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA=1;//發送I2C總線結束信號  
}
//等待應答信號到來
//返回值：1，接收應答失敗
//        0，接收應答成功
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA設置為輸入  
	CT_IIC_SDA=1;	   
	CT_IIC_SCL=1;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL=0;//時鐘輸出0 	   
	return 0;  
} 
//產生ACK應答
void CT_IIC_Ack(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=0;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}
//不產生ACK應答		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=1;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}					 				     
//IIC發送一個字節
//返回從機有無應答
//1，有應答
//0，無應答			  
void CT_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL=0;//拉低時鐘開始數據傳輸
	CT_Delay();
	for(t=0;t<8;t++)
    {              
        CT_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	      
		CT_IIC_SCL=1; 
		CT_Delay();
		CT_IIC_SCL=0;	
		CT_Delay();
    }	 
} 	    
//讀1個字節，ack=1時，發送ACK，ack=0，發送nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA設置為輸入
	delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL=0; 	    	   
		CT_Delay();
		CT_IIC_SCL=1;	 
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//發送nACK
	else CT_IIC_Ack(); //發送ACK   
 	return receive;
}





























