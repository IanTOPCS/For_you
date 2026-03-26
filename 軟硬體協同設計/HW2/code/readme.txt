實驗器材:
	探索者STM32F4開發板
	
實驗目的:
	學習彩色TFTLCD顯示屏的使用
	
硬件資源:
	1,DS0(連接在PF9) 
	2,串口1(波特率:115200,PA9/PA10連接在板載USB轉串口芯片CH340上面)
	3,ALIENTEK 2.8/3.5/4.3/7寸TFTLCD模塊(通過FSMC驅動,FSMC_NE4接LCD片選/A6接RS) 
	
實驗現象:
	本實驗利用探索者STM32開發板連接ALIENTEK TFTLCD模塊(除CPLD版本7寸屏模塊外,其餘所有ALIENTEK的
	LCD模塊都可以支持)，實現TFTLCD模塊的顯示，下載成功後，通過把LCD模塊插入TFTLCD模塊接口（靠右
	插），按下復位之後，就可以看到LCD模塊不停的顯示一些信息並不斷切換底色。同時該實驗會顯示LCD驅
	動器的ID，並且會在串口打印（按復位一次，打印一次）。
	
注意事項: 
	1,4.3寸和7寸屏需要比較大電流,USB供電可能不足,請用外部電源適配器(推薦外接12V 1A電源).
	2,本例程在LCD_Init函數里面(在ILI93xx.c),用到了printf,如果不初始化串口1,將導致液晶無法顯示!! 


					正點原子@ALIENTEK
					2014-10-25
					廣州市星翼電子科技有限公司
					電話：020-38271790
					傳真：020-36773971
					購買：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司網站：www.alientek.com
					技術論壇：www.openedv.com
					
					
					
					
					
					
					
					
					
					