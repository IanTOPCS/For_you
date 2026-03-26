#include "exti.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���{�ǥu�ѾǲߨϥΡA���g�@�̳\�i�A���o�Ω�䥦����γ~
//ALIENTEK STM32F407�}�o�O
//�~�����_ �X�ʥN�X	   
//���I��l@ALIENTEK
//�޳N�׾�:www.openedv.com
//�Ыؤ��:2014/5/4
//�����GV1.0
//���v�Ҧ��A�s�����s�C
//Copyright(C) �s�{���P�l�q�l��ަ������q 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
//�~�����_��l�Ƶ{��
//��l��PE2~4,PA0�����_��J.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	//KEY_Init(); //���������IO�f��l��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//�ϯ�SYSCFG����
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 �s���줤�_�u2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);//PE3 �s���줤�_�u3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 �s���줤�_�u4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 �s���줤�_�u0
	
  /* �t�mEXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//���_�ƥ�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�W�ɪuĲ�o 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ϯ�LINE0
  EXTI_Init(&EXTI_InitStructure);//�t�m
	
	/* �t�mEXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//���_�ƥ�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�U���uĲ�o
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//���_�u�ϯ�
  EXTI_Init(&EXTI_InitStructure);//�t�m
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�~�����_0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//�m���u����0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�l�u����2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ϯ�~�����_�q�D
  NVIC_Init(&NVIC_InitStructure);//�t�m
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�~�����_2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//�m���u����3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�l�u����2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ϯ�~�����_�q�D
  NVIC_Init(&NVIC_InitStructure);//�t�m
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�~�����_3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//�m���u����2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�l�u����2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ϯ�~�����_�q�D
  NVIC_Init(&NVIC_InitStructure);//�t�m
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�~�����_4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//�m���u����1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�l�u����2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//�ϯ�~�����_�q�D
  NVIC_Init(&NVIC_InitStructure);//�t�m
	   
}












