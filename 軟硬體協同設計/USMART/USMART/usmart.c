#include "usmart.h"
#include "usart.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供學習使用，未經作者許可，不得用於其它任何用途
//ALIENTEK STM32開發板	   
//正點原子@ALIENTEK
//技術論壇:www.openedv.com 
//版本：V3.1
//版權所有，盜版必究。
//Copyright(C) 正點原子 2011-2021
//All rights reserved
//********************************************************************************
//升級說明
//V1.4
//增加了對參數為string類型的函數的支持.適用範圍大大提高.
//優化了內存佔用,靜態內存佔用為79個字節@10個參數.動態適應數字及字符串長度
//V2.0 
//1,修改了list指令,打印函數的完整表達式.
//2,增加了id指令,打印每個函數的入口地址.
//3,修改了參數匹配,支持函數參數的調用(輸入入口地址).
//4,增加了函數名長度宏定義.	
//V2.1 20110707		 
//1,增加dec,hex兩個指令,用於設置參數顯示進制,及執行進制轉換.
//注:當dec,hex不帶參數的時候,即設定顯示參數進制.當後跟參數的時候,即執行進制轉換.
//如:"dec 0XFF" 則會將0XFF轉為255,由串口返回.
//如:"hex 100" 	則會將100轉為0X64,由串口返回
//2,新增usmart_get_cmdname函數,用於獲取指令名字.
//V2.2 20110726	
//1,修正了void類型參數的參數統計錯誤.
//2,修改數據顯示格式默認為16進制.
//V2.3 20110815
//1,去掉了函數名後必須跟"("的限制.
//2,修正了字符串參數中不能有"("的bug.
//3,修改了函數默認顯示參數格式的修改方式. 
//V2.4 20110905
//1,修改了usmart_get_cmdname函數,增加最大參數長度限制.避免了輸入錯誤參數時的死機現象.
//2,增加USMART_ENTIM2_SCAN宏定義,用於配置是否使用TIM2定時執行scan函數.
//V2.5 20110930
//1,修改usmart_init函數為void usmart_init(u8 sysclk),可以根據系統頻率自動設定掃瞄時間.(固定100ms)
//2,去掉了usmart_init函數中的uart_init函數,串口初始化必須在外部初始化,方便用戶自行管理.
//V2.6 20111009
//1,增加了read_addr和write_addr兩個函數.可以利用這兩個函數讀寫內部任意地址(必須是有效地址).更加方便調試.
//2,read_addr和write_addr兩個函數可以通過設置USMART_USE_WRFUNS為來使能和關閉.
//3,修改了usmart_strcmp,使其規範化.			  
//V2.7 20111024
//1,修正了返回值16進制顯示時不換行的bug.
//2,增加了函數是否有返回值的判斷,如果沒有返回值,則不會顯示.有返回值時才顯示其返回值.
//V2.8 20111116
//1,修正了list等不帶參數的指令發送後可能導致死機的bug.
//V2.9 20120917
//1,修改了形如：void*xxx(void)類型函數不能識別的bug。
//V3.0 20130425
//1,新增了字符串參數對轉義符的支持。
//V3.1 20131120
//1,增加runtime系統指令,可以用於統計函數執行時間.
//用法:
//發送:runtime 1 ,則開啟函數執行時間統計功能
//發送:runtime 0 ,則關閉函數執行時間統計功能
///runtime統計功能,必須設置:USMART_ENTIMX_SCAN 為1,才可以使用!!
/////////////////////////////////////////////////////////////////////////////////////
//系統命令
u8 *sys_cmd_tab[]=
{
	"?",
	"help",
	"list",
	"id",
	"hex",
	"dec",
	"runtime",	   
};	    
//處理系統指令
//0,成功處理;其他,錯誤代碼;
u8 usmart_sys_cmd_exe(u8 *str)
{
	u8 i;
	u8 sfname[MAX_FNAME_LEN];//存放本地函數名
	u8 pnum;
	u8 rval;
	u32 res;  
	res=usmart_get_cmdname(str,sfname,&i,MAX_FNAME_LEN);//得到指令及指令長度
	if(res)return USMART_FUNCERR;//錯誤的指令 
	str+=i;	 	 			    
	for(i=0;i<sizeof(sys_cmd_tab)/4;i++)//支持的系統指令
	{
		if(usmart_strcmp(sfname,sys_cmd_tab[i])==0)break;
	}
	switch(i)
	{					   
		case 0:
		case 1://幫助指令
			printf("\r\n");
#if USMART_USE_HELP
			printf("------------------------USMART V3.1------------------------ \r\n");
			printf("    USMART是由ALIENTEK開發的一個靈巧的串口調試互交組件,通過 \r\n");
			printf("它,你可以通過串口助手調用程序裡面的任何函數,並執行.因此,你可\r\n");
			printf("以隨意更改函數的輸入參數(支持數字(10/16進制)、字符串、函數入\r\n");	  
			printf("口地址等作為參數),單個函數最多支持10個輸入參數,並支持函數返 \r\n");
			printf("回值顯示.新增參數顯示進制設置功能,新增進制轉換功能.\r\n");
			printf("技術支持:www.openedv.com\r\n");
			printf("USMART有7個系統命令:\r\n");
			printf("?:      獲取幫助信息\r\n");
			printf("help:   獲取幫助信息\r\n");
			printf("list:   可用的函數列表\r\n\n");
			printf("id:     可用函數的ID列表\r\n\n");
			printf("hex:    參數16進制顯示,後跟空格+數字即執行進制轉換\r\n\n");
			printf("dec:    參數10進制顯示,後跟空格+數字即執行進制轉換\r\n\n");
			printf("runtime:1,開啟函數運行計時;0,關閉函數運行計時;\r\n\n");
			printf("請按照程序編寫格式輸入函數名及參數並以回車鍵結束.\r\n");    
			printf("--------------------------ALIENTEK------------------------- \r\n");
#else
			printf("指令失效\r\n");
#endif
			break;
		case 2://查詢指令
			printf("\r\n");
			printf("-------------------------函數清單--------------------------- \r\n");
			for(i=0;i<usmart_dev.fnum;i++)printf("%s\r\n",usmart_dev.funs[i].name);
			printf("\r\n");
			break;	 
		case 3://查詢ID
			printf("\r\n");
			printf("-------------------------函數 ID --------------------------- \r\n");
			for(i=0;i<usmart_dev.fnum;i++)
			{
				usmart_get_fname((u8*)usmart_dev.funs[i].name,sfname,&pnum,&rval);//得到本地函數名 
				printf("%s id is:\r\n0X%08X\r\n",sfname,usmart_dev.funs[i].func); //顯示ID
			}
			printf("\r\n");
			break;
		case 4://hex指令
			printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//參數正常
			{
				i=usmart_str2num(sfname,&res);	   	//記錄該參數	
				if(i==0)						  	//進制轉換功能
				{
					printf("HEX:0X%X\r\n",res);	   	//轉為16進制
				}else if(i!=4)return USMART_PARMERR;//參數錯誤.
				else 				   				//參數顯示設定功能
				{
					printf("16進制參數顯示!\r\n");
					usmart_dev.sptype=SP_TYPE_HEX;  
				}

			}else return USMART_PARMERR;			//參數錯誤.
			printf("\r\n"); 
			break;
		case 5://dec指令
			printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//參數正常
			{
				i=usmart_str2num(sfname,&res);	   	//記錄該參數	
				if(i==0)						   	//進制轉換功能
				{
					printf("DEC:%lu\r\n",res);	   	//轉為10進制
				}else if(i!=4)return USMART_PARMERR;//參數錯誤.
				else 				   				//參數顯示設定功能
				{
					printf("10進制參數顯示!\r\n");
					usmart_dev.sptype=SP_TYPE_DEC;  
				}

			}else return USMART_PARMERR;			//參數錯誤. 
			printf("\r\n"); 
			break;	 
		case 6://runtime指令,設置是否顯示函數執行時間
			printf("\r\n");
			usmart_get_aparm(str,sfname,&i);
			if(i==0)//參數正常
			{
				i=usmart_str2num(sfname,&res);	   		//記錄該參數	
				if(i==0)						   		//讀取指定地址數據功能
				{
					if(USMART_ENTIMX_SCAN==0)printf("\r\nError! \r\nTo EN RunTime function,Please set USMART_ENTIMX_SCAN = 1 first!\r\n");//報錯
					else
					{
						usmart_dev.runtimeflag=res;
						if(usmart_dev.runtimeflag)printf("Run Time Calculation ON\r\n");
						else printf("Run Time Calculation OFF\r\n"); 
					}
				}else return USMART_PARMERR;   			//未帶參數,或者參數錯誤	 
 			}else return USMART_PARMERR;				//參數錯誤. 
			printf("\r\n"); 
			break;	    
		default://非法指令
			return USMART_FUNCERR;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
//移植注意:本例是以stm32為例,如果要移植到其他mcu,請做相應修改.
//usmart_reset_runtime,清除函數運行時間,連同定時器的計數寄存器以及標誌位一起清零.並設置重裝載值為最大,以最大限度的延長計時時間.
//usmart_get_runtime,獲取函數運行時間,通過讀取CNT值獲取,由於usmart是通過中斷調用的函數,所以定時器中斷不再有效,此時最大限度
//只能統計2次CNT的值,也就是清零後+溢出一次,當溢出超過2次,沒法處理,所以最大延時,控制在:2*計數器CNT*0.1ms.對STM32來說,是:13.1s左右
//其他的:TIM4_IRQHandler和Timer4_Init,需要根據MCU特點自行修改.確保計數器計數頻率為:10Khz即可.另外,定時器不要開啟自動重裝載功能!!

#if USMART_ENTIMX_SCAN==1
//復位runtime
//需要根據所移植到的MCU的定時器參數進行修改
void usmart_reset_runtime(void)
{
 
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//清除中斷標誌位 
	TIM_SetAutoreload(TIM4,0XFFFF);//將重裝載值設置到最大
	TIM_SetCounter(TIM4,0);		//清空定時器的CNT
	usmart_dev.runtime=0;	
}
//獲得runtime時間
//返回值:執行時間,單位:0.1ms,最大延時時間為定時器CNT值的2倍*0.1ms
//需要根據所移植到的MCU的定時器參數進行修改
u32 usmart_get_runtime(void)
{
	if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//在運行期間,產生了定時器溢出
	{
		usmart_dev.runtime+=0XFFFF;
	}
	usmart_dev.runtime+=TIM_GetCounter(TIM4);
	return usmart_dev.runtime;		//返回計數值
}  
//下面這兩個函數,非USMART函數,放到這裡,僅僅方便移植. 
//定時器4中斷服務程序	 
void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//溢出中斷
	{
		usmart_dev.scan();	//執行usmart掃瞄	
		TIM_SetCounter(TIM4,0);		//清空定時器的CNT
		TIM_SetAutoreload(TIM4,100);//恢復原來的設置		    				   				     	    	
	}				   
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中斷標誌位    
}
//使能定時器4,使能中斷.
void Timer4_Init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM4時鐘

	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定時器分頻
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上計數模式
	TIM_TimeBaseInitStructure.TIM_Period=arr;   //自動重裝載值
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化定時器4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允許定時器4更新中斷
	TIM_Cmd(TIM4,ENABLE); //使能定時器4
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//外部中斷4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//搶佔優先級3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子優先級3
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中斷通道
  NVIC_Init(&NVIC_InitStructure);//配置NVIC
	 							 
}
#endif
////////////////////////////////////////////////////////////////////////////////////////
//初始化串口控制器
//sysclk:系統時鐘（Mhz）
void usmart_init(u8 sysclk)
{
#if USMART_ENTIMX_SCAN==1
	Timer4_Init(1000,(u32)sysclk*100-1);//分頻,時鐘為10K ,100ms中斷一次,注意,計數頻率必須為10Khz,以和runtime單位(0.1ms)同步.
#endif
	usmart_dev.sptype=1;	//十六進制顯示參數
}		
//從str中獲取函數名,id,及參數信息
//*str:字符串指針.
//返回值:0,識別成功;其他,錯誤代碼.
u8 usmart_cmd_rec(u8*str) 
{
	u8 sta,i,rval;//狀態	 
	u8 rpnum,spnum;
	u8 rfname[MAX_FNAME_LEN];//暫存空間,用於存放接收到的函數名  
	u8 sfname[MAX_FNAME_LEN];//存放本地函數名
	sta=usmart_get_fname(str,rfname,&rpnum,&rval);//得到接收到的數據的函數名及參數個數	  
	if(sta)return sta;//錯誤
	for(i=0;i<usmart_dev.fnum;i++)
	{
		sta=usmart_get_fname((u8*)usmart_dev.funs[i].name,sfname,&spnum,&rval);//得到本地函數名及參數個數
		if(sta)return sta;//本地解析有誤	  
		if(usmart_strcmp(sfname,rfname)==0)//相等
		{
			if(spnum>rpnum)return USMART_PARMERR;//參數錯誤(輸入參數比源函數參數少)
			usmart_dev.id=i;//記錄函數ID.
			break;//跳出.
		}	
	}
	if(i==usmart_dev.fnum)return USMART_NOFUNCFIND;	//未找到匹配的函數
 	sta=usmart_get_fparam(str,&i);					//得到函數參數個數	
	if(sta)return sta;								//返回錯誤
	usmart_dev.pnum=i;								//參數個數記錄
    return USMART_OK;
}
//usamrt執行函數
//該函數用於最終執行從串口收到的有效函數.
//最多支持10個參數的函數,更多的參數支持也很容易實現.不過用的很少.一般5個左右的參數的函數已經很少見了.
//該函數會在串口打印執行情況.以:"函數名(參數1，參數2...參數N)=返回值".的形式打印.
//當所執行的函數沒有返回值的時候,所打印的返回值是一個無意義的數據.
void usmart_exe(void)
{
	u8 id,i;
	u32 res;		   
	u32 temp[MAX_PARM];//參數轉換,使之支持了字符串 
	u8 sfname[MAX_FNAME_LEN];//存放本地函數名
	u8 pnum,rval;
	id=usmart_dev.id;
	if(id>=usmart_dev.fnum)return;//不執行.
	usmart_get_fname((u8*)usmart_dev.funs[id].name,sfname,&pnum,&rval);//得到本地函數名,及參數個數 
	printf("\r\n%s(",sfname);//輸出正要執行的函數名
	for(i=0;i<pnum;i++)//輸出參數
	{
		if(usmart_dev.parmtype&(1<<i))//參數是字符串
		{
			printf("%c",'"');			 
			printf("%s",usmart_dev.parm+usmart_get_parmpos(i));
			printf("%c",'"');
			temp[i]=(u32)&(usmart_dev.parm[usmart_get_parmpos(i)]);
		}else						  //參數是數字
		{
			temp[i]=*(u32*)(usmart_dev.parm+usmart_get_parmpos(i));
			if(usmart_dev.sptype==SP_TYPE_DEC)printf("%lu",temp[i]);//10進制參數顯示
			else printf("0X%X",temp[i]);//16進制參數顯示 	   
		}
		if(i!=pnum-1)printf(",");
	}
	printf(")");
	usmart_reset_runtime();	//計時器清零,開始計時
	switch(usmart_dev.pnum)
	{
		case 0://無參數(void類型)											  
			res=(*(u32(*)())usmart_dev.funs[id].func)();
			break;
	    case 1://有1個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0]);
			break;
	    case 2://有2個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1]);
			break;
	    case 3://有3個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2]);
			break;
	    case 4://有4個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3]);
			break;
	    case 5://有5個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4]);
			break;
	    case 6://有6個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5]);
			break;
	    case 7://有7個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6]);
			break;
	    case 8://有8個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7]);
			break;
	    case 9://有9個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7],temp[8]);
			break;
	    case 10://有10個參數
			res=(*(u32(*)())usmart_dev.funs[id].func)(temp[0],temp[1],temp[2],temp[3],temp[4],\
			temp[5],temp[6],temp[7],temp[8],temp[9]);
			break;
	}
	usmart_get_runtime();//獲取函數執行時間
	if(rval==1)//需要返回值.
	{
		if(usmart_dev.sptype==SP_TYPE_DEC)printf("=%lu;\r\n",res);//輸出執行結果(10進制參數顯示)
		else printf("=0X%X;\r\n",res);//輸出執行結果(16進制參數顯示)	   
	}else printf(";\r\n");		//不需要返回值,直接輸出結束
	if(usmart_dev.runtimeflag)	//需要顯示函數執行時間
	{ 
		printf("Function Run Time:%d.%1dms\r\n",usmart_dev.runtime/10,usmart_dev.runtime%10);//打印函數執行時間 
	}	
}
//usmart掃瞄函數
//通過調用該函數,實現usmart的各個控制.該函數需要每隔一定時間被調用一次
//以及時執行從串口發過來的各個函數.
//本函數可以在中斷裡面調用,從而實現自動管理.
//如果非ALIENTEK用戶,則USART_RX_STA和USART_RX_BUF[]需要用戶自己實現
void usmart_scan(void)
{
	u8 sta,len;  
	if(USART_RX_STA&0x8000)//串口接收完成？
	{					   
		len=USART_RX_STA&0x3fff;	//得到此次接收到的數據長度
		USART_RX_BUF[len]='\0';	//在末尾加入結束符. 
		sta=usmart_dev.cmd_rec(USART_RX_BUF);//得到函數各個信息
		if(sta==0)usmart_dev.exe();	//執行函數 
		else 
		{  
			len=usmart_sys_cmd_exe(USART_RX_BUF);
			if(len!=USMART_FUNCERR)sta=len;
			if(sta)
			{
				switch(sta)
				{
					case USMART_FUNCERR:
						printf("函數錯誤!\r\n");   			
						break;	
					case USMART_PARMERR:
						printf("參數錯誤!\r\n");   			
						break;				
					case USMART_PARMOVER:
						printf("參數太多!\r\n");   			
						break;		
					case USMART_NOFUNCFIND:
						printf("未找到匹配的函數!\r\n");   			
						break;		
				}
			}
		}
		USART_RX_STA=0;//狀態寄存器清空	    
	}
}

#if USMART_USE_WRFUNS==1 	//如果使能了讀寫操作
//讀取指定地址的值		 
u32 read_addr(u32 addr)
{
	return *(u32*)addr;//	
}
//在指定地址寫入指定的值		 
void write_addr(u32 addr,u32 val)
{
	*(u32*)addr=val; 	
}
#endif













