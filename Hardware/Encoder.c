#include "stm32f10x.h"                  // Device header
/*
* Function   
* @date           
* @brief        编码器初始化，一个编码器占用一个定时器
* @param[in]   void
* @param[out]    void
* @retval    
* @par History   
*/
void Encoder1_Init(void)
{
//开启系统时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU; //原则上和外部模块默认电平一致
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//配置TIM
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStruct);
	
	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 A8
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_4;   //选择通道 A11
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM1,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM1,ENABLE);
}

void Encoder2_Init(void)
{
//开启系统时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置输出的GPIO口
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU; //原则上和外部模块默认电平一致
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//配置TIM
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=(65536-1);      //自动重装载计数器(ARR)
	TIM_TimeBaseInitStruct.TIM_Prescaler=(1 -1);   //预分频值(PSC)
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;   //高级定时器功能
	
	TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStruct);
	
	//配置输入捕获
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);          //赋初值
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;   //选择通道 A1
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	
	
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;   //选择通道 A0
	TIM_ICInitStruct.TIM_ICFilter=0xF;            //滤波器
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
	               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //不反向
				   
	TIM_Cmd(TIM2,ENABLE);
}


/*
* Function   
* @date           
* @brief        获取编码器计数值
* @param[in]   void
* @param[out]    temp
* @retval    
* @par History   
*/
int16_t Encoder1_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1,0);
return temp;
}

int16_t Encoder2_Get(void)
{
	int16_t temp;
	temp=TIM_GetCounter(TIM2);
	TIM_SetCounter(TIM2,0);
return temp;
	
}
