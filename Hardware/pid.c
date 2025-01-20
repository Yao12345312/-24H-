#include "stm32f10x.h"                  // Device header
#include "IMU.h"
#include "Encoder.h"
#include "motor.h"
#include "MPU6050.h"

//直立环控制(PD)
float Vertical_Kp=-867;  //-867
float Vertical_Kd=-1041.6; //-1041.6

//速度环
float Velocity_Kp=19.19;  //19.19
float Velocity_Ki=0.09595;  //0.09595

//转向环
float Trun_Kp=0;   //30
float Trun_Kd=0; //3000


int16_t Vertical(float Expect_Angle,float Current_Angle,float gyro_y)
{
	int16_t PWM_Out;
PWM_Out= Vertical_Kp*(Current_Angle-Expect_Angle)+Vertical_Kd*gyro_y;
	return  PWM_Out;
}

int16_t Velocity(float Expect_Speed,int16_t Encoder_Left,int16_t Encoder_Right)
{
	static int Encoder_Err,Encoder_Err_Lowout,Encoder_Err_Lowout_last,Encoder_Sum,PWM_Out;
	Encoder_Err=(Encoder_Left+Encoder_Right)-Expect_Speed; //编码器误差
	//一阶速度滤波
	Encoder_Err*=0.3;
	Encoder_Err_Lowout_last*=0.7;//当last取大时，平顺性好，灵敏度低，last取小时相反
	
	Encoder_Err_Lowout=Encoder_Err+Encoder_Err_Lowout_last;
	Encoder_Err_Lowout_last=Encoder_Err_Lowout;
	
	Encoder_Sum+=Encoder_Err_Lowout;
	//积分限幅
	Encoder_Sum=Encoder_Sum>8000?8000:(Encoder_Sum<(-8000)?(-8000):Encoder_Sum);
	//PI控制
	PWM_Out=Velocity_Kp*Encoder_Err_Lowout+Velocity_Ki*Encoder_Sum;
	
	return PWM_Out;
}

//转向环
int16_t Turn(float Expect_Yaw,float gyro_z )
{
	int16_t PWM_Out=0;
	if(Expect_Yaw==0)
	{
		PWM_Out=Trun_Kd*gyro_z;
	}
else
	{
		PWM_Out=Trun_Kp*(Expect_Yaw-imu_Angle.Yaw);
	}
	
return PWM_Out;
}

//位置环

