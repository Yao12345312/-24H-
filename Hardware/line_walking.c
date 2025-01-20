#include "stm32f10x.h"                  // Device header
#include "Line_walking.h" 
#include "Delay.h"
void Line_Walking_Gpio_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
#ifdef USE_LINE_L1
	
	RCC_APB2PeriphClockCmd(LineWalk_L1_RCC, ENABLE); 
																   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_L1_PIN;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  	GPIO_Init(LineWalk_L1_PORT, &GPIO_InitStructure);		 
#endif

#ifdef USE_LINE_L2
	
	RCC_APB2PeriphClockCmd(LineWalk_L2_RCC, ENABLE); 
																   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_L2_PIN;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  	GPIO_Init(LineWalk_L2_PORT, &GPIO_InitStructure);	
#endif

#ifdef USE_LINE_R1
	
	RCC_APB2PeriphClockCmd(LineWalk_R1_RCC, ENABLE); 
																   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_R1_PIN;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  	GPIO_Init(LineWalk_R1_PORT, &GPIO_InitStructure);	
#endif
	
#ifdef USE_LINE_R2
	
	RCC_APB2PeriphClockCmd(LineWalk_R2_RCC, ENABLE); 
																   
  	GPIO_InitStructure.GPIO_Pin = LineWalk_R2_PIN;	
	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
  	GPIO_Init(LineWalk_R2_PORT, &GPIO_InitStructure);	
#endif

}

void GetLineWalking(int *p_iL1, int *p_iL2, int *p_iR1, int *p_iR2)
{
	*p_iL1 = GPIO_ReadInputDataBit(LineWalk_L1_PORT, LineWalk_L1_PIN);
	*p_iL2 = GPIO_ReadInputDataBit(LineWalk_L2_PORT, LineWalk_L2_PIN);
	*p_iR1 = GPIO_ReadInputDataBit(LineWalk_R1_PORT, LineWalk_R1_PIN);
	*p_iR2 = GPIO_ReadInputDataBit(LineWalk_R2_PORT, LineWalk_R2_PIN);		
}

void LineWalking(void)
{
	int LineL1 = 1, LineL2 = 1, LineR1 = 1, LineR2 = 1;

	GetLineWalking(&LineL1, &LineL2, &LineR1, &LineR2);	//获取黑线检测状态	

	if( (LineL1 == 0 || LineL2 == 0) && LineR2 == 0) //左大弯
    {
      	//Car_SpinLeft(7000, 7000);
		Delay_ms(80);
    }
    else if ( LineL1 == 0 && (LineR1 == 0 || LineR2 == 0)) //右大弯
	{ 
      	//Car_SpinRight(7000, 7000);
		Delay_ms(80);
    }  
    else if( LineL1 == 0 ) //左最外侧检测
    {  
		//Car_SpinLeft(6800, 6800);
		Delay_ms(10);
	}
    else if ( LineR2 == 0) //右最外侧检测
    {  
		//Car_SpinRight(6800, 6800);
		Delay_ms(10);
	}
    else if (LineL2 == 0 && LineR1 == 1) //中间黑线上的传感器微调车左转
    {   
		//Car_Left(6500);   
	}
	else if (LineL2 == 1 && LineR1 == 0) //中间黑线上的传感器微调车右转
    {   
		//Car_Right(6500);   
	}
    else if(LineL2 == 0 && LineR1 == 0) // 都是黑色, 加速前进
    {  
		//Car_Run(7200);
	}	
}
