#include "usmart_str.h"
#include "usmart.h"		   
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
  
//對比字符串str1和str2
//*str1:字符串1指針
//*str2:字符串2指針
//返回值:0，相等;1，不相等;
u8 usmart_strcmp(u8 *str1,u8 *str2)
{
	while(1)
	{
		if(*str1!=*str2)return 1;//不相等
		if(*str1=='\0')break;//對比完成了.
		str1++;
		str2++;
	}
	return 0;//兩個字符串相等
}
//把str1的內容copy到str2
//*str1:字符串1指針
//*str2:字符串2指針			   
void usmart_strcopy(u8*str1,u8 *str2)
{
	while(1)
	{										   
		*str2=*str1;	//拷貝
		if(*str1=='\0')break;//拷貝完成了.
		str1++;
		str2++;
	}
}
//得到字符串的長度(字節)
//*str:字符串指針
//返回值:字符串的長度		   
u8 usmart_strlen(u8*str)
{
	u8 len=0;
	while(1)
	{							 
		if(*str=='\0')break;//拷貝完成了.
		len++;
		str++;
	}
	return len;
}
//m^n函數
//返回值:m^n次方
u32 usmart_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	    
//把字符串轉為數字
//支持16進制轉換,但是16進制字母必須是大寫的,且格式為以0X開頭的.
//不支持負數 
//*str:數字字符串指針
//*res:轉換完的結果存放地址.
//返回值:0，成功轉換完成.其他,錯誤代碼.
//1,數據格式錯誤.2,16進制位數為0.3,起始格式錯誤.4,十進制位數為0.
u8 usmart_str2num(u8*str,u32 *res)
{
	u32 t;
	u8 bnum=0;	//數字的位數
	u8 *p;		  
	u8 hexdec=10;//默認為十進制數據
	p=str;
	*res=0;//清零.
	while(1)
	{
		if((*p<='9'&&*p>='0')||(*p<='F'&&*p>='A')||(*p=='X'&&bnum==1))//參數合法
		{
			if(*p>='A')hexdec=16;	//字符串中存在字母,為16進制格式.
			bnum++;					//位數增加.
		}else if(*p=='\0')break;	//碰到結束符,退出.
		else return 1;				//不全是十進制或者16進制數據.
		p++; 
	} 
	p=str;			    //重新定位到字符串開始的地址.
	if(hexdec==16)		//16進制數據
	{
		if(bnum<3)return 2;			//位數小於3，直接退出.因為0X就佔了2個,如果0X後面不跟數據,則該數據非法.
		if(*p=='0' && (*(p+1)=='X'))//必須以'0X'開頭.
		{
			p+=2;	//偏移到數據起始地址.
			bnum-=2;//減去偏移量	 
		}else return 3;//起始頭的格式不對
	}else if(bnum==0)return 4;//位數為0，直接退出.	  
	while(1)
	{
		if(bnum)bnum--;
		if(*p<='9'&&*p>='0')t=*p-'0';	//得到數字的值
		else t=*p-'A'+10;				//得到A~F對應的值	    
		*res+=t*usmart_pow(hexdec,bnum);		   
		p++;
		if(*p=='\0')break;//數據都查完了.	
	}
	return 0;//成功轉換
}
//得到指令名
//*str:源字符串
//*cmdname:指令名
//*nlen:指令名長度		
//maxlen:最大長度(做限制,指令不可能太長的)	
//返回值:0,成功;其他,失敗.	  
u8 usmart_get_cmdname(u8*str,u8*cmdname,u8 *nlen,u8 maxlen)
{
	*nlen=0;
 	while(*str!=' '&&*str!='\0') //找到空格或者結束符則認為結束了
	{
		*cmdname=*str;
		str++;
		cmdname++;
		(*nlen)++;//統計命令長度
		if(*nlen>=maxlen)return 1;//錯誤的指令
	}
	*cmdname='\0';//加入結束符
	return 0;//正常返回
}
//獲取下一個字符（當中間有很多空格的時候，此函數直接忽略空格，找到空格之後的第一個字符）
//str:字符串指針	
//返回值:下一個字符
u8 usmart_search_nextc(u8* str)
{		   	 	
	str++;
	while(*str==' '&&str!='\0')str++;
	return *str;
} 
//從str中得到函數名
//*str:源字符串指針
//*fname:獲取到的函數名字指針
//*pnum:函數的參數個數
//*rval:是否需要顯示返回值(0,不需要;1,需要)
//返回值:0,成功;其他,錯誤代碼.
u8 usmart_get_fname(u8*str,u8*fname,u8 *pnum,u8 *rval)
{
	u8 res;
	u8 fover=0;	  //括號深度
	u8 *strtemp;
	u8 offset=0;  
	u8 parmnum=0;
	u8 temp=1;
	u8 fpname[6];//void+X+'/0'
	u8 fplcnt=0; //第一個參數的長度計數器
	u8 pcnt=0;	 //參數計數器
	u8 nchar;
	//判斷函數是否有返回值
	strtemp=str;
	while(*strtemp!='\0')//沒有結束
	{
		if(*strtemp!=' '&&(pcnt&0X7F)<5)//最多記錄5個字符
		{	
			if(pcnt==0)pcnt|=0X80;//置位最高位,標記開始接收返回值類型
			if(((pcnt&0x7f)==4)&&(*strtemp!='*'))break;//最後一個字符,必須是*
			fpname[pcnt&0x7f]=*strtemp;//記錄函數的返回值類型
			pcnt++;
		}else if(pcnt==0X85)break;
		strtemp++; 
	} 
	if(pcnt)//接收完了
	{
		fpname[pcnt&0x7f]='\0';//加入結束符
		if(usmart_strcmp(fpname,"void")==0)*rval=0;//不需要返回值
		else *rval=1;							   //需要返回值
		pcnt=0;
	} 
	res=0;
	strtemp=str;
	while(*strtemp!='('&&*strtemp!='\0') //此代碼找到函數名的真正起始位置
	{  
		strtemp++;
		res++;
		if(*strtemp==' '||*strtemp=='*')
		{
			nchar=usmart_search_nextc(strtemp);		//獲取下一個字符
			if(nchar!='('&&nchar!='*')offset=res;	//跳過空格和*號
		}
	}	 
	strtemp=str;
	if(offset)strtemp+=offset+1;//跳到函數名開始的地方	   
	res=0;
	nchar=0;//是否正在字符串裡面的標誌,0，不在字符串;1，在字符串;
	while(1)
	{
		if(*strtemp==0)
		{
			res=USMART_FUNCERR;//函數錯誤
			break;
		}else if(*strtemp=='('&&nchar==0)fover++;//括號深度增加一級	 
		else if(*strtemp==')'&&nchar==0)
		{
			if(fover)fover--;
			else res=USMART_FUNCERR;//錯誤結束,沒收到'('
			if(fover==0)break;//到末尾了,退出	    
		}else if(*strtemp=='"')nchar=!nchar;

		if(fover==0)//函數名還沒接收完
		{
			if(*strtemp!=' ')//空格不屬於函數名
			{
				*fname=*strtemp;//得到函數名
				fname++;
			}
		}else //已經接受完了函數名了.
		{
			if(*strtemp==',')
			{
				temp=1;		//使能增加一個參數
				pcnt++;	
			}else if(*strtemp!=' '&&*strtemp!='(')
			{
				if(pcnt==0&&fplcnt<5)		//當第一個參數來時,為了避免統計void類型的參數,必須做判斷.
				{
					fpname[fplcnt]=*strtemp;//記錄參數特徵.
					fplcnt++;
				}
				temp++;	//得到有效參數(非空格)
			}
			if(fover==1&&temp==2)
			{
				temp++;		//防止重複增加
				parmnum++; 	//參數增加一個
			}
		}
		strtemp++; 			
	}   
	if(parmnum==1)//只有1個參數.
	{
		fpname[fplcnt]='\0';//加入結束符
		if(usmart_strcmp(fpname,"void")==0)parmnum=0;//參數為void,表示沒有參數.
	}
	*pnum=parmnum;	//記錄參數個數
	*fname='\0';	//加入結束符
	return res;		//返回執行結果
}


//從str中得到一個函數的參數
//*str:源字符串指針
//*fparm:參數字符串指針
//*ptype:參數類型 0，數字;1，字符串;0XFF，參數錯誤
//返回值:0,已經無參數了;其他,下一個參數的偏移量.
u8 usmart_get_aparm(u8 *str,u8 *fparm,u8 *ptype)
{
	u8 i=0;
	u8 enout=0;
	u8 type=0;//默認是數字
	u8 string=0; //標記str是否正在讀
	while(1)
	{		    
		if(*str==','&& string==0)enout=1;			//暫緩立即退出,目的是尋找下一個參數的起始地址
		if((*str==')'||*str=='\0')&&string==0)break;//立即退出標識符
		if(type==0)//默認是數字的
		{
			if((*str>='0' && *str<='9')||(*str>='a' && *str<='f')||(*str>='A' && *str<='F')||*str=='X'||*str=='x')//數字串檢測
			{
				if(enout)break;					//找到了下一個參數,直接退出.
				if(*str>='a')*fparm=*str-0X20;	//小寫轉換為大寫
				else *fparm=*str;		   		//小寫或者數字保持不變
				fparm++;
			}else if(*str=='"')//找到字符串的開始標誌
			{
				if(enout)break;//找到,後才找到",認為結束了.
				type=1;
				string=1;//登記STRING 正在讀了
			}else if(*str!=' '&&*str!=',')//發現非法字符,參數錯誤
			{
				type=0XFF;
				break;
			}
		}else//string類
		{ 
			if(*str=='"')string=0;
			if(enout)break;			//找到了下一個參數,直接退出.
			if(string)				//字符串正在讀
			{	
				if(*str=='\\')		//遇到轉義符(不複製轉義符)
				{ 
					str++;			//偏移到轉義符後面的字符,不管什麼字符,直接COPY
					i++;
				}					
				*fparm=*str;		//小寫或者數字保持不變
				fparm++;
			}	
		}
		i++;//偏移量增加
		str++;
	}
	*fparm='\0';	//加入結束符
	*ptype=type;	//返回參數類型
	return i;		//返回參數長度
}
//得到指定參數的起始地址
//num:第num個參數,範圍0~9.
//返回值:該參數的起始地址
u8 usmart_get_parmpos(u8 num)
{
	u8 temp=0;
	u8 i;
	for(i=0;i<num;i++)temp+=usmart_dev.plentbl[i];
	return temp;
}
//從str中得到函數參數
//str:源字符串;
//parn:參數的多少.0表示無參數 void類型
//返回值:0,成功;其他,錯誤代碼.
u8 usmart_get_fparam(u8*str,u8 *parn)
{	
	u8 i,type;  
	u32 res;
	u8 n=0;
	u8 len;
	u8 tstr[PARM_LEN+1];//字節長度的緩存,最多可以存放PARM_LEN個字符的字符串
	for(i=0;i<MAX_PARM;i++)usmart_dev.plentbl[i]=0;//清空參數長度表
	while(*str!='(')//偏移到參數開始的地方
	{
		str++;											    
		if(*str=='\0')return USMART_FUNCERR;//遇到結束符了
	}
	str++;//偏移到"("之後的第一個字節
	while(1)
	{
		i=usmart_get_aparm(str,tstr,&type);	//得到第一個參數  
		str+=i;								//偏移
		switch(type)
		{
			case 0:	//數字
				if(tstr[0]!='\0')				//接收到的參數有效
				{					    
					i=usmart_str2num(tstr,&res);	//記錄該參數	 
					if(i)return USMART_PARMERR;		//參數錯誤.
					*(u32*)(usmart_dev.parm+usmart_get_parmpos(n))=res;//記錄轉換成功的結果.
					usmart_dev.parmtype&=~(1<<n);	//標記數字
					usmart_dev.plentbl[n]=4;		//該參數的長度為4  
					n++;							//參數增加  
					if(n>MAX_PARM)return USMART_PARMOVER;//參數太多
				}
				break;
			case 1://字符串	 	
				len=usmart_strlen(tstr)+1;	//包含了結束符'\0'
				usmart_strcopy(tstr,&usmart_dev.parm[usmart_get_parmpos(n)]);//拷貝tstr數據到usmart_dev.parm[n]
				usmart_dev.parmtype|=1<<n;	//標記字符串 
				usmart_dev.plentbl[n]=len;	//該參數的長度為len  
				n++;
				if(n>MAX_PARM)return USMART_PARMOVER;//參數太多
				break;
			case 0XFF://錯誤
				return USMART_PARMERR;//參數錯誤	  
		}
		if(*str==')'||*str=='\0')break;//查到結束標誌了.
	}
	*parn=n;	//記錄參數的個數
	return USMART_OK;//正確得到了參數
}














