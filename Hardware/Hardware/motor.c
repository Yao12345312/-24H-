#include "stm32f10x.h"                  // Device header
#include "PWM.h" 
#include "IMU.h"
int16_t PWM_MAX=7200; 
int16_t PWM_MIN=-7200;

/*
* Function   
* @date          2025/1/8 
* @brief        电机逻辑端口初始化
* @param[in]   void
* @param[out]    void
* @retval    
* @par History   
*/
void Motor_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//控制方向引脚初始化（AIN1,2;BIN1,2）
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP; //开漏输出
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	
	
}
/*
* Function   
* @date           2025/1/8
* @brief        控制电机正反转
* @param[in]   int16_t Speed
* @param[out]    
* @retval    
* @par History   
*/
void Left_Motor_Speed(int16_t Speed) //左电机
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_4); //给INA1高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	PWM_SetCompare1(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_5); //给INA2高电平
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	PWM_SetCompare1(-Speed);
	}
}

void Right_Motor_Speed(int16_t Speed) //右电机
{
	if(Speed>=0)  //正转
	{
	GPIO_SetBits(GPIOB,GPIO_Pin_14); //给INB1高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	PWM_SetCompare2(Speed);
	}
	else		  //反转
	{
	GPIO_SetBits(GPIOB,GPIO_Pin_15); //给INB2高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	PWM_SetCompare2(-Speed);
	}
}
/*
* Function   
* @date           
* @brief        电机转速限制
* @param[in]   Left_Speed Right_Speed
* @param[out]    void
* @retval    
* @par History   
*/
void Motor_Limitation(float* Left_Speed , float* Right_Speed)
{
	//左电机限速
	if(*Left_Speed>PWM_MAX)
	{
	*Left_Speed=PWM_MAX;
	}
	if(*Left_Speed<PWM_MIN)
	{
	*Left_Speed=PWM_MIN;
	}
	//右电机限速
	if(*Right_Speed>PWM_MAX)
	{
	*Right_Speed=PWM_MAX;
	}
	if(*Right_Speed<PWM_MIN)
	{
	*Right_Speed=PWM_MIN;
	}
	if(imu_Angle.Roll>40||imu_Angle.Roll<-40) //倾角太大救不了了，防止烧坏电机
	{
	*Left_Speed=0;
	*Right_Speed=0;
	}
}
