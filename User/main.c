#include "stm32f10x.h"                  // Device header
  
#include "OLED.h"  
#include "MPU6050.h"
#include "EXTI.h"
#include "TIM.h"
#include "IMU.h"
#include "Encoder.h"
#include "motor.h"
#include "pid.h"
#include "PWM.h"
#include "USART.h"


uint8_t MPU_6050_IT_Flag;
uint8_t USART_RxFlag;
uint16_t USART_RxData;

int16_t Encoder_Left_Speed,Encoder_Right_Speed;  //编码器速度

float Mechanical_median=-1;		//机械中值，精确到小数点后2位
float Expect_Speed=0;		//转向时期待的速度
float Expect_Turn_Angle=0;

float Vertical_Out;  			//直立环输出
float Velocity_Out;			//速度环输出
float Turn_Out;				//转向环输出

float LeftMotor_Out;			//左电机输出
float RightMotor_Out;			//右电机输出
float PWM_Out;				//最终输出


int main(void)
{
    OLED_Init();
	//Serial_Init();
	MPU6050_Init();
	MPU6050_EXTI_Init();
	PWM_Init();
	Motor_Init();
	Encoder1_Init();
	Encoder2_Init();
	OLED_ShowString(1, 1,"OLED_Ready");
	
 while(1)
	{   
		if(MPU_6050_IT_Flag==1)//这个能不能直接放到外部中断里面执行？
		{
		MPU_6050_IT_Flag=0;
		Encoder_Left_Speed=Encoder1_Get();
		Encoder_Right_Speed=Encoder2_Get();
			
		IMU_getEuleranAngles(); //当EXTI中断来时刷新MPU6050数据
		
		Vertical_Out=Vertical(Mechanical_median,imu_Angle.Roll,imu_data.GX); //直立环
		
		Velocity_Out=Velocity(Expect_Speed,Encoder_Left_Speed,Encoder_Right_Speed); //速度环
		
		//Turn_Out=Turn(Expect_Turn_Angle,imu_data.GZ );//转向环
//串级pid控制：
		LeftMotor_Out=Vertical_Out+Velocity_Out;//-Turn_Out;	
		RightMotor_Out=Vertical_Out+Velocity_Out;//+Turn_Out;
		
		Motor_Limitation(&LeftMotor_Out,&RightMotor_Out);//输出传递到电机
		
		//Left_Motor_Speed(LeftMotor_Out);
		//Right_Motor_Speed(RightMotor_Out);
		
		//喂狗

		}
		
		OLED_ShowFNum(3,1,imu_Angle.Roll,3);
		OLED_ShowSignedNum(4,1,imu_data.GX, 5);
		
	 }
}

//MPU6050中断函数
void  EXTI0_IRQHandler(void) 
{
if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
		MPU_6050_IT_Flag=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
		//每次程序结束后都应该清除中断标志位
	}
}
/*
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{ 
	USART_RxFlag=1;
	USART_RxData=USART_ReceiveData(USART1);	
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
	}
}
*/
/*void TIM4_IRQHandler(void)  //中断函数
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
	    Encoder_Left_Speed=Encoder1_Get()/11/4/21.3*60;
		Encoder_Right_Speed=Encoder2_Get()/11/4/21.3*60; //编码器测得脉冲数/磁极数/单位周期内计数/减速比*1min
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}
*/
