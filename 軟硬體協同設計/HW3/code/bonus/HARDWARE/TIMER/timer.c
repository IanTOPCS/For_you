#include "timer.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���{�ǥu�ѾǲߨϥΡA���g�@�̳\�i�A���o�Ω�䥦����γ~
//ALIENTEK STM32F407�}�o�O
//�w�ɾ� �X�ʥN�X	   
//���I��l@ALIENTEK
//�޳N�׾�:www.openedv.com
//�Ыؤ��:2014/5/4
//�����GV1.0
//���v�Ҧ��A�s�����s�C
//Copyright(C) �s�{���P�l�q�l��ަ������q 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


//�q�Ωw�ɾ�3���_��l��
//arr�G�۰ʭ��˭ȡC
//psc�G�����w���W��
//�w�ɾ����X�ɶ��p���k:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=�w�ɾ��u�@�W�v,���:Mhz
//�o�̨ϥΪ��O�w�ɾ�3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///�ϯ�TIM3����
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�۰ʭ��˸���
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //�w�ɾ����W
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�V�W�p�ƼҦ�
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��l��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //���\�w�ɾ�3��s���_
	TIM_Cmd(TIM3,ENABLE); //�ϯ�w�ɾ�3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //�w�ɾ�3���_
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //�m���u����1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�l�u����3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
