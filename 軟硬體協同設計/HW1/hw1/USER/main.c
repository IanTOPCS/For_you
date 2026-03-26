#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "exti.h"
#include <string.h>

//ALIENTEK 探索者STM32F407開發板 實驗5
//外部中斷實驗-庫函數版本
//技術支持：www.openedv.com
//淘寶店舖：http://eboard.taobao.com
//廣州市星翼電子科技有限公司    
//作者：正點原子 @ALIENTEK 

u8 en0 = 0, en1 = 0, en2 = 0;

int main(void) { 
	u8 len = 0, keyNum = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//設置系統中斷優先級分組2
	delay_init(168);    //初始化延時函數
	uart_init(115200); 	//串口初始化 
	LED_Init();				  //初始化LED端口  
	BEEP_Init();        //初始化蜂鳴器端口
	EXTIX_Init();       //初始化外部中斷輸入 
	LED0=0, LED1 = 0;					    //先點亮紅燈
	en0 = 1, en1 = 1, en2 = 1;
	while(1) {
		if(USART_RX_STA&0x8000) {					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的數據長度
			if ((len == 6) || (len == 7)) {
				// dis? EN
				if (len == 6) {
					// en
					if (strncmp((char*)USART_RX_BUF, "ENKEY", 5) == 0) {
						keyNum = USART_RX_BUF[5]-'0';
						if (keyNum == 0) {
							// enable key0
							en0 = 1;
						} else if (keyNum == 1) {
							// enable key1
							en1 = 1;
						} else if (keyNum == 2) {
							// enable key2
							en2 = 1;
						}
					}
				} else if (len == 7) {
					// dis
					if (strncmp((char*)USART_RX_BUF, "DISKEY", 6) == 0) {
						keyNum = USART_RX_BUF[6]-'0';
						if (keyNum == 0) {
							// disable key0
							en0 = 0;
						} else if (keyNum == 1) {
							// disable key1
							en1 = 0;
						} else if (keyNum == 2) {
							// disable key2
							en2 = 0;
						}
					}
				}
			}
			USART_RX_STA=0;
		}
	}
}
