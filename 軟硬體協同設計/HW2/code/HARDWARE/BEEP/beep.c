#include "beep.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32F407開發板
//蜂鳴器驅動代碼	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com
//創建日期:2014/5/3
//版本：V1.0
//版權所有，盜版必究。
//Copyright(C) 廣州市星翼電子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PF8為輸出口		    
//BEEP IO初始化
void BEEP_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF時鐘
  
  //初始化蜂鳴器對應引腳GPIOF8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//BEEP對應引腳
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通輸出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽輸出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	
  GPIO_ResetBits(GPIOF,GPIO_Pin_8);  //蜂鳴器對應引腳GPIOF8拉低， 
}






