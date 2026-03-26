#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//按鍵輸入驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/3
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//按鍵初始化函數
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE時鐘
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; //KEY0 KEY1 KEY2對應引腳
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通輸入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP對應引腳PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0
 
} 
//按鍵處理函數
//返回按鍵值
//mode:0,不支持連續按;1,支持連續按;
//0，沒有任何按鍵按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函數有響應優先級,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按鍵按鬆開標誌
	if(mode)key_up=1;  //支持連按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//去抖動 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(WK_UP==1)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
 	return 0;// 無按鍵按下
}




















