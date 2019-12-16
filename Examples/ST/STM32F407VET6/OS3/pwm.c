#include "pwm.h"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

/* dead time setting */
uint16_t DeadTime = 0x20;
/* starting output PWM ratio */
uint32_t ccr_temp = 50;

void TIM1_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	/* enable CLK */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC,ENABLE);
	/* enable PIN's AF function */
	/* TIM1_CH1  PA8 */
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
	/* TIM1_CH1N PE8 */
	/* enable PE8's AF function as the clk source of pwm output negtive side */
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);
	/* TIM8_CH1N PA5 */
  /* GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM8); */
	/* TIM8_CH1 PC6 */
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);
	/* PIN configuration below share the same function as below, be careful */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;													//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;												//�ٶ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      											//���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        											//����
	/* enable PC6's GPIO function as the pos-side of the output signal */
	/* PC6 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
#if 0
	/* PE8 */
	/* disable PE8's GPIO function because we use the neg-side of the output signal by connecting to PA8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_Init(GPIOE,&GPIO_InitStructure);
#endif 
	/* PA8 */
	/* enable PA8's GPIO function as the neg-side of the output signal */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;											//�����趨 
	GPIO_Init(GPIOA,&GPIO_InitStructure);			

}

void Tim1__Config(void)
{
	u32 TimerPeriod,ccr1;
	TimerPeriod=  (168000000 / Freq ) - 1;  
	ccr1 = TimerPeriod / 2;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8,ENABLE);  

	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_Period = TimerPeriod;
	//������ʽ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	//���ﲻ��
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//�ظ�������
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ָ��ʱ�ӷ�Ƶ
	//��ʼ����ʱ��
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);   //��ʼ����ʱ��1
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);   //��ʼ����ʱ��8


	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;				//ָ��������ģʽ��ʹ�õĹر�״̬ѡ��
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;				//ָ������״̬��ʹ�õĹر�״̬
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;					//ָ��LOCK����Ĳ���
	TIM_BDTRInitStructure.TIM_DeadTime = DeadTime;							//ָ���رպ������֮ͨ����ӳ�ʱ��  ����ʱ����ֵ��ʱ������
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;					//ָ���Ƿ�����Break����
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;		//ָ��TIM�ж����ż���
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;	//ָ���Ƿ�����TIM�Զ��������
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;          		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�ƶ�TIM�Ƚ����״̬  ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //�ƶ�TIM��������Ƚ�״̬  ʹ��
	TIM_OCInitStructure.TIM_Pulse = 50;								//ռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;      //�������:TIM��������Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;		//ָ������״̬�ڼ��TIM����Ƚ�����״̬(����1)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;	//ָ������״̬�ڼ��TIM����Ƚ�����״̬(����N)
	TIM_OC1Init(TIM8,&TIM_OCInitStructure);                         //����Tָ���Ĳ�����ʼ������
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);                         //����Tָ���Ĳ�����ʼ������
	TIM_OCInitStructure.TIM_Pulse = ccr1;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;				//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2	
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);	
	
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC2Ref); 			//ѡ��TIMx�������ģʽ
	TIM_SelectInputTrigger(TIM8, TIM_TS_ITR0);    					//ѡ�����봥��Դ  �ڲ�����0
	TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);     			//ѡ��TIMx��ģʽ
	
	TIM_Cmd(TIM1,ENABLE);                                          //ʹ��TIM1
	TIM_Cmd(TIM8,ENABLE);                                          //ʹ��TIM8
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                               //ʹ��PWM���
	TIM_CtrlPWMOutputs(TIM8,ENABLE);                               //ʹ��PWM���
}

void Buck_GPIO_Config(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	/* enable CLK */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	/* PIN configuration below share the same function as below, be careful */
    /* Pin output configure */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;													//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;												//�ٶ�
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      											//���츴�����
    /* pull up for disable voltage output */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        				
	/* enable PC6's GPIO function as the pos-side of the output signal */
	/* PD4*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}







