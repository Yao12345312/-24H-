#include "stm32f10x.h"                  // Device header


/*
* Function   
* @date           
* @brief        陀螺仪外部中断初始化，
* @param[in]   void
* @param[out]  void  
* @retval    
* @par History   
*/
void MPU6050_EXTI_Init(void)
{	//开启外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU; //上拉输入
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	
	//配置EXTI 
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //下降沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	
    //配置NVIC 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn; //选择通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;  //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;         //响应优先级
	
	NVIC_Init(&NVIC_InitStructure);
}

