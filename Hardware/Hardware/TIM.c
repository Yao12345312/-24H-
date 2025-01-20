#include "stm32f10x.h"  // Device header


/*
* Function   
* @date           
* @brief        定时器4初始化
* @param[in]   void
* @param[out]    void
* @retval    
* @par History   
*/
void Timer_Init(void)
{ 
	//开启系统时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//配置TIM
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStruct.TIM_Period=(10000-1);      //自动重装载计数器
	TIM_TimeBaseInitStruct.TIM_Prescaler=(7200 -1);   //预分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	//计时频率：1hz
	//时基初始化
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStruct);
	//配置中断
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //选择通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;         //响应优先级
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4, ENABLE);  //启用TIM外设
}



