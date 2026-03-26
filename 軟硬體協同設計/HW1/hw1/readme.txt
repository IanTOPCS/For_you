實驗器材:
	探索者STM32F4開發板
	
實驗目的:
	學習外部中斷的使用
	
硬件資源:
	1,DS0(連接在PF9) 
	2,蜂鳴器(連接在PF8) 
	3,按鍵KEY0(PE4)/KEY1(PE3)/KEY2(PE2)/KEY_UP(PA0,也稱之為WK_UP)
	
	
實驗現象:
	本實驗,利用外部中斷，實現與實驗3類似的效果，即：通過開發板上載有的4個按
	鈕（KEY_UP、KEY0、KEY1和KEY2），來控制板上的2個LED（DS0和DS1）和蜂鳴器
	，其中WK_UP控制蜂鳴器，按一次叫，再按一次停；KEY2控制DS0，按一次亮，再按
	一次滅；KEY1控制DS1，效果同KEY2；KEY0則同時控制DS0和DS1，按一次，他們的
	狀態就翻轉一次。
	
注意事項:
	無. 
	 
	 
					正點原子@ALIENTEK
					2014-10-25
					廣州市星翼電子科技有限公司
					電話：020-38271790
					傳真：020-36773971
					購買：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司網站：www.alientek.com
					技術論壇：www.openedv.com
					
					
					
					
					
					
					
					
					
					
					
					
					
					