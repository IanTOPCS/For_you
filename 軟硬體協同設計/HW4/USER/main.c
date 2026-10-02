#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "touch.h" 
#include "usmart.h"
#include "myDrawBigPoint.h"
#include "exti.h"

int main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(115200);
	usmart_dev.init(84); 	//初始化USMART			

	LED_Init();
 	LCD_Init();
	KEY_Init();
	EXTIX_Init();
	tp_dev.init();				//觸摸屏初始化
 	POINT_COLOR=RED;
	// init grid
	initGridInfo();
	printGrid();
	while(1) {
		// erase warring
		if (KEY2 == 0) {
			destructor();
			break;
		}
	}
	return 0;
}

// key-0 stop painting on LCD
void EXTI4_IRQHandler(void) {
	delay_ms(10);
	if(KEY0==0) {				 
		drawFlag = false;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);
}

// key-1 switch color-mode (0: pen, 1: colorful)
void EXTI3_IRQHandler(void) {
	delay_ms(10);
	if(KEY1==0) {
		colorMode = !colorMode;
		if (colorMode == true) {
			LED0 = 0;
		} else {
			LED0 = 1;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);
}
