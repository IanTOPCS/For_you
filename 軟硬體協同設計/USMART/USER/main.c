#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "usmart.h"


//ALIENTEK 贝STM32F407秨祇狾 龟喷14
//USMART秸刚龟喷 -畐ㄧ计セ
//м砃やwww.openedv.com
//瞊腳┍鏓http://eboard.taobao.com  
//約カ琍羖筿мΤそ  
//タ翴 @ALIENTEK


//LED篈砞竚ㄧ计
void led_set(u8 sta)
{
	LED1=sta;
} 
//ㄧ计把计秸ノ代刚ㄧ计
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}  


int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//砞竚╰参い耞纔だ舱2
	delay_init(168);      //﹍て┑ㄧ计
	uart_init(115200);		//﹍て﹃猧疭瞯115200
	usmart_dev.init(84); 	//﹍てUSMART			
	LED_Init();					  //﹍てLED
 	LCD_Init();           //﹍てLCD
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/5");	   
  	while(1) 
	{		 	  
		LED0=!LED0;					 
		delay_ms(500);	
	}
}
