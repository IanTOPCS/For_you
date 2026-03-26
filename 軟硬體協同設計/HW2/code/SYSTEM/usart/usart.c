#include "sys.h"
#include "usart.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,則包括下面的頭文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F4探索者開發板
//串口1初始化		   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//修改日期:2014/6/10
//版本：V1.5
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改說明 
//支持適應不同頻率下的串口波特率設置.
//加入了對printf的支持
//增加了串口接收命令功能.
//修正了printf第一個字符丟失的bug
//V1.4修改說明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字節數為2的14次方
//3,增加了USART_REC_LEN,用於定義串口最大允許接收的字節數(不大於2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改說明
//1,增加了對UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代碼,支持printf函數,而不需要選擇use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//標準庫需要的支持函數                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定義_sys_exit()以避免使用半主機模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定義fputc函數 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循環發送,直到發送完畢   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART1_RX   //如果使能了接收
//串口1中斷服務程序
//注意,讀取USARTx->SR能避免莫名其妙的錯誤   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收緩衝,最大USART_REC_LEN個字節.
//接收狀態
//bit15，	接收完成標誌
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字節數目
u16 USART_RX_STA=0;       //接收狀態標記	

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
   //GPIO端口設置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA時鐘
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1時鐘
 
	//串口1對應引腳復用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9復用為USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10復用為USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9與GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//復用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽復用輸出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化設置
	USART_InitStructure.USART_BaudRate = bound;//波特率設置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字長為8位數據格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一個停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//無奇偶校驗位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//無硬件數據流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收發模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//開啟相關中斷

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中斷通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//搶佔優先級3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子優先級3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根據指定的參數初始化VIC寄存器、

#endif
	
}


void USART1_IRQHandler(void)                	//串口1中斷服務程序
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS為真，則需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中斷(接收到的數據必須是0x0d 0x0a結尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//讀取接收到的數據
		
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//接收錯誤,重新開始
				else USART_RX_STA|=0x8000;	//接收完成了 
			}
			else //還沒收到0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收數據錯誤,重新開始接收	  
				}		 
			}
		}   		 
  } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS為真，則需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	

 



