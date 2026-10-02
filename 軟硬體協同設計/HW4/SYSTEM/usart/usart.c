#include "sys.h"
#include "usart.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//�p�G�ϥ�ucos,�h�]�A�U�����Y���Y�i.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos �ϥ�	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//���{�ǥu�ѾǲߨϥΡA���g�@�̳\�i�A���o�Ω�䥦����γ~
//ALIENTEK STM32F4�����̶}�o�O
//��f1��l��		   
//���I��l@ALIENTEK
//�޳N�׾�:www.openedv.com
//�ק���:2014/6/10
//�����GV1.5
//���v�Ҧ��A�s�����s�C
//Copyright(C) �s�{���P�l�q�l��ަ������q 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�קﻡ�� 
//����A�����P�W�v�U����f�i�S�v�]�m.
//�[�J�F��printf�����
//�W�[�F��f�����R�O�\��.
//�ץ��Fprintf�Ĥ@�Ӧr�ťᥢ��bug
//V1.4�קﻡ��
//1,�ק��f��l��IO��bug
//2,�ק�FUSART_RX_STA,�ϱo��f�̤j�����r�`�Ƭ�2��14����
//3,�W�[�FUSART_REC_LEN,�Ω�w�q��f�̤j���\�������r�`��(���j��2��14����)
//4,�ק�FEN_USART1_RX���ϯ�覡
//V1.5�קﻡ��
//1,�W�[�F��UCOSII�����
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�[�J�H�U�N�X,���printf���,�Ӥ��ݭn���use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//�зǮw�ݭn��������                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//�w�q_sys_exit()�H�קK�ϥΥb�D���Ҧ�    
_sys_exit(int x) 
{ 
	x = x; 
} 
//���w�qfputc��� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//�`���o�e,����o�e����   
	USART1->DR = (u8) ch;      
	return ch;
}

void _ttywrch(int ch)
{
    ch = ch;
}

#endif
 
#if EN_USART1_RX   //�p�G�ϯ�F����
//��f1���_�A�ȵ{��
//�`�N,Ū��USARTx->SR���קK���W�䧮�����~   	
u8 USART_RX_BUF[USART_REC_LEN];     //�����w��,�̤jUSART_REC_LEN�Ӧr�`.
//�������A
//bit15�A	���������лx
//bit14�A	������0x0d
//bit13~0�A	�����쪺���Ħr�`�ƥ�
u16 USART_RX_STA=0;       //�������A�аO	

//��l��IO ��f1 
//bound:�i�S�v
void uart_init(u32 bound){
   //GPIO�ݤf�]�m
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //�ϯ�GPIOA����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//�ϯ�USART1����
 
	//��f1�����޸}�_�άM�g
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9�_�ά�USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10�_�ά�USART1
	
	//USART1�ݤf�t�m
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9�PGPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//�_�Υ\��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�t��50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�����_�ο�X
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //�W��
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��l��PA9�APA10

   //USART1 ��l�Ƴ]�m
	USART_InitStructure.USART_BaudRate = bound;//�i�S�v�]�m
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�r����8��ƾڮ榡
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//�@�Ӱ����
	USART_InitStructure.USART_Parity = USART_Parity_No;//�L�_�������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//�L�w��ƾڬy����
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//���o�Ҧ�
  USART_Init(USART1, &USART_InitStructure); //��l�Ʀ�f1
	
  USART_Cmd(USART1, ENABLE);  //�ϯ��f1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�}�Ҭ������_

	//Usart1 NVIC �t�m
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//��f1���_�q�D
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//�m���u����3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�l�u����3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ�q�D�ϯ�
	NVIC_Init(&NVIC_InitStructure);	//�ھګ��w���Ѽƪ�l��VIC�H�s���B

#endif
	
}


void USART1_IRQHandler(void)                	//��f1���_�A�ȵ{��
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//�p�GSYSTEM_SUPPORT_OS���u�A�h�ݭn���OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�������_(�����쪺�ƾڥ����O0x0d 0x0a����)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//Ū�������쪺�ƾ�
		
		if((USART_RX_STA&0x8000)==0)//����������
		{
			if(USART_RX_STA&0x4000)//������F0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//�������~,���s�}�l
				else USART_RX_STA|=0x8000;	//���������F 
			}
			else //�٨S����0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�����ƾڿ��~,���s�}�l����	  
				}		 
			}
		}   		 
  } 
#if SYSTEM_SUPPORT_OS 	//�p�GSYSTEM_SUPPORT_OS���u�A�h�ݭn���OS.
	OSIntExit();  											 
#endif
} 
#endif	

 



