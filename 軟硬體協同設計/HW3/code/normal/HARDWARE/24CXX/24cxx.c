#include "24cxx.h" 
#include "delay.h" 				 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//24CXX 驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/6
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//初始化IIC接口
void AT24CXX_Init(void)
{
	IIC_Init();//IIC初始化
}
//在AT24CXX指定地址讀出一個數據
//ReadAddr:開始讀數的地址  
//返回值  :讀到的數據
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //發送寫命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//發送高地址	    
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //發送器件地址0XA0,寫數據 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //發送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //進入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//產生一個停止條件	    
	return temp;
}
//在AT24CXX指定地址寫入一個數據
//WriteAddr  :寫入數據的目的地址    
//DataToWrite:要寫入的數據
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //發送寫命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//發送高地址	  
	}else IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //發送器件地址0XA0,寫數據 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //發送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //發送字節							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//產生一個停止條件 
	delay_ms(10);	 
}
//在AT24CXX裡面的指定地址開始寫入長度為Len的數據
//該函數用於寫入16bit或者32bit的數據.
//WriteAddr  :開始寫入的地址  
//DataToWrite:數據數組首地址
//Len        :要寫入數據的長度2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX裡面的指定地址開始讀出長度為Len的數據
//該函數用於讀出16bit或者32bit的數據.
//ReadAddr   :開始讀出的地址 
//返回值     :數據
//Len        :要讀出數據的長度2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//檢查AT24CXX是否正常
//這裡用了24XX的最後一個地址(255)來存儲標誌字.
//如果用其他24C系列,這個地址要修改
//返回1:檢測失敗
//返回0:檢測成功
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次開機都寫AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情況
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX裡面的指定地址開始讀出指定個數的數據
//ReadAddr :開始讀出的地址 對24c02為0~255
//pBuffer  :數據數組首地址
//NumToRead:要讀出數據的個數
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX裡面的指定地址開始寫入指定個數的數據
//WriteAddr :開始寫入的地址 對24c02為0~255
//pBuffer   :數據數組首地址
//NumToWrite:要寫入數據的個數
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}








