#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
//GREEN 
#define LED1_PIN                  GPIO_Pin_9                
#define LED1_GPIO_PORT            GPIOE                      
#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOE

//BLUE 
#define LED2_PIN                  GPIO_Pin_10                 
#define LED2_GPIO_PORT            GPIOE                      
#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOE

/************************************************************/


/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  1
#define OFF 0

/* ���κ꣬��������������һ��ʹ�� */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define LED1_TOGGLE		digitalToggle(LED1_GPIO_PORT,LED1_PIN)
#define LED1_OFF			digitalLo(LED1_GPIO_PORT,LED1_PIN)
#define LED1_ON				digitalHi(LED1_GPIO_PORT,LED1_PIN)

#define LED2_TOGGLE		digitalToggle(LED2_GPIO_PORT,LED2_PIN)
#define LED2_OFF			digitalLo(LED2_GPIO_PORT,LED2_PIN)
#define LED2_ON				digitalHi(LED2_GPIO_PORT,LED2_PIN)

#define LED3_TOGGLE		digitalToggle(LED3_GPIO_PORT,LED3_PIN)
#define LED3_OFF			digitalLo(LED3_GPIO_PORT,LED3_PIN)
#define LED3_ON				digitalHi(LED3_GPIO_PORT,LED3_PIN)

#define LED_ALLOFF	\
					LED1_OFF;\
					LED2_OFF;




void LED_GPIO_Config(void);

#endif /* __LED_H */
