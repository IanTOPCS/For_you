#include "timer.h"
#include "led.h"

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

void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///�ϯ�TIM3����
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�۰ʭ��˸���
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //�w�ɾ����W
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�V�W�p�ƼҦ�
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��l��TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //���\�w�ɾ�3��s���_
	TIM_Cmd(TIM4,ENABLE); //�ϯ�w�ɾ�3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //�w�ɾ�3���_
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //�m���u����1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�l�u����3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///�ϯ�TIM3����
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�۰ʭ��˸���
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //�w�ɾ����W
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //�V�W�p�ƼҦ�
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��l��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //���\�w�ɾ�3��s���_
	TIM_Cmd(TIM5,ENABLE); //�ϯ�w�ɾ�3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //�w�ɾ�3���_
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //�m���u����1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�l�u����3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
