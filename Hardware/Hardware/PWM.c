#include "stm32f10x.h"                  // Device header

/*
* Function   
* @date           
* @brief        电机PWM电机调速，定时器初始化
* @param[in]   void
* @param[out]    void
* @retval    
* @par History   
*/
void PWM_Init()
{

	//开启系统时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7; //a6为CH1，a7为CH2
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//配置TIM
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //计数模式：向上计数
	TIM_TimeBaseInitStruct.TIM_Period=(7200-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStruct);
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//不知道哪些成员要用，就先都配个初始值
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=0;    //设置CCR寄存器,占空比=CCR/(ARR+1)
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	
	TIM_Cmd(TIM3, ENABLE);  //启用TIM外设
}

/*
* Function   
* @date           
* @brief        调节PWM占空比以控制转速
* @param[in]   Compare
* @param[out]    void
* @retval    
* @par History   
*/
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3,Compare);
} 

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM3,Compare);
}


