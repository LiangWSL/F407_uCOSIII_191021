#ifndef _TIMER_H
#define _TIMER_H
#include  "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define Freq (150000)

extern uint16_t DeadTime;
extern uint32_t ccr_temp;
#define BUCK(a)	if (a)	\
					GPIO_SetBits(GPIOD,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOD,GPIO_Pin_4)
                      
void TIM1_PWM_Init(u32 arr,u32 psc);
void TIM1_GPIO_Config(void);
void Buck_GPIO_Config(void);
void Tim1__Config(void);

#endif
