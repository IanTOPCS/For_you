#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "timer.h"
#include "key.h"
#include "exti.h"

// radious of circle
u8 r = 12;
u16 x = 0, y = 0;
u8 rightFg = 0, leftFg = 0, upFg = 0, downFg = 0, smallFg = 0, bigFg = 0;

// remind user the key is already work (addition)
u8 ledFg = 0, showStudentId = 0, cnt = 0, ledCnt = 0;
// show student-id (addition)
u8 fontSize = 16, fontIndex = 0;
// fixed student-id (addition)
u8 studentId[8] = {0, 1, 2, 5, 7, 0, 2, 7};

int main(void) {
	KEY_Init();
	EXTIX_Init();
	delay_init(168);
	// why this fucking shit can enable LCD?
	uart_init(115200);
	// counter is 84M, 84M/8400=10kHz, 10kHz*500=50ms
	TIM3_Int_Init(500-1,8400-1);
	// counter is 84M, 84M/8400=10kHz, 10kHz*5000=500ms (addition)
	TIM4_Int_Init(5000-1,8400-1);
	// counter is 84M, 84M/8400=10kHz, 10kHz*100=10ms (addition)
	TIM5_Int_Init(100-1,8400-1);
	LCD_Init();
	LED_Init();
	// set background equal "black"
	LCD_Clear(BLACK);
	// set pencil color equal "red"
	POINT_COLOR=RED;
	// set default x, y at middle of LCD
	x = (lcddev.width)/2, y = (lcddev.height)/2;
  	while(1) {
		// if press key0 
		if (KEY0 == 0) {
			// debounce
			delay_ms(10);
			while(KEY0 == 0);
			// during 2 timer 4 interrupt => 500ms*2=1s
			if (cnt >= 2) {
				if (showStudentId == 0) {
					fontIndex = 0, showStudentId = 1;
				}
				else showStudentId = 0;
			}
		}
		cnt = 0;
	}
	return 0;
}

// timer 3 interrupt
void TIM3_IRQHandler(void) {
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) {
		// reset LCD
		LCD_Clear(BLACK);
		
		// enable go right but encounter right border
		if ((rightFg == 1) && ((x+r)<lcddev.width)) x++;
		else if (rightFg == 1) {
			// change direction to left
			rightFg = 0, leftFg = 1;
			x--;
		}

		// enable go left but encounter left border
		if ((leftFg == 1) && ((x-r)>0)) x--;
		else if (leftFg == 1) {
			// change direction to right
			rightFg = 1, leftFg = 0;
			x++;
		}

		// enable go up but encounter up border
		if ((upFg == 1) && ((y+r)<lcddev.height)) y++;
		else if (upFg == 1) {
			// change direction to down
			upFg = 0, downFg = 1;
			y--;
		}

		// enable go down but encounter down border
		if ((downFg == 1) && ((y-r)>0)) y--;
		else if (downFg == 1) {
			// change direction to up
			upFg = 1, downFg = 0;
			y++;
		}

		// radious turn small (r/2 can't little than font size)
		if ((smallFg == 1) && ((r*2)>fontSize)) r--;

		// radious can't bigger than width of LCD
		if ((bigFg == 1) && (((x+r)<lcddev.width) && ((x-r)>0) && ((y+r)<lcddev.height) && ((y-r)>0))) r++;

		// draw circle when timer 3 interrupt
		LCD_Draw_Circle(x, y, r);

		// show student-id
		if (showStudentId == 1) {
			LCD_ShowxNum(x-(fontSize/4), y-(fontSize/2), (u32)studentId[fontIndex], 1, fontSize, 1);
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

// timer 4 interrupt (addition)
void TIM4_IRQHandler(void) {
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) {
		cnt++;
		fontIndex = (fontIndex+1)%8;
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}

// timer 5 interrupt (addition)
void TIM5_IRQHandler(void) {
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) {
		// shine 10ms*100=1000 ms
		if ((ledFg == 1) && (ledCnt < 100)) {
			LED0 = 0, ledCnt++;
		} else {
			LED0 = 1, ledCnt = 0, ledFg = 0;
		};
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
}

void EXTI0_IRQHandler(void) {
	// debounce
	delay_ms(10);
	if(WK_UP==1) {
		// remind user the function is working right now
		if (smallFg == 1) ledFg = 1;
		else {
			// turn circle small
			smallFg = 1, bigFg = 0;
			// disable any direction
			leftFg = 0, rightFg = 0, upFg = 0, downFg = 0;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line0);
}	

void EXTI2_IRQHandler(void) {
	delay_ms(10);
	if(KEY2==0) {
		// remind user the function is working right now
		if ((leftFg == 1) || (rightFg == 1)) ledFg = 1;
		else {
			// disable big and small
			smallFg = 0, bigFg = 0;
			// disable up and down
			upFg = 0, downFg = 0;  
			// default go right, else go left
			rightFg = 1, leftFg = 0;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void) {
	delay_ms(10);
	if(KEY1==0) {
		// remind user the function is working right now
		if (bigFg == 1) ledFg = 1;
		else {
			// turn circle big
			smallFg = 0, bigFg = 1;
			// disable any direction
			leftFg = 0, rightFg = 0, upFg = 0, downFg = 0;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void) {
	delay_ms(10);
	if(KEY0==0) {
		// remind user the function is working right now
		if ((upFg == 1) || (downFg == 1)) ledFg = 1;
		else {
			// disable big and small
			smallFg = 0, bigFg = 0;	 
			// disable left and right
			leftFg = 0, rightFg = 0;
			// default go up, else go down
			upFg = 1, downFg = 0;
		}
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);
}
