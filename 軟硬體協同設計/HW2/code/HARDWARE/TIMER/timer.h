#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//���{�ǥu�ѾǲߨϥΡA���g�@�̳\�i�A���o�Ω�䥦����γ~
//ALIENTEK STM32F407�}�o�O
//�w�ɾ� �X�ʥN�X	   
//���I��l@ALIENTEK
//�޳N�׾�:www.openedv.com
//�Ыؤ��:2014/6/16
//�����GV1.0
//���v�Ҧ��A�s�����s�C
//Copyright(C) �s�{���P�l�q�l��ަ������q 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM5_Int_Init(u16 arr,u16 psc);
#endif
