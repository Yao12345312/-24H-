#ifndef __Line_walking_H__
#define __Line_walking_H__

#define USE_LINE_L1
#define USE_LINE_L2
#define USE_LINE_R1
#define USE_LINE_R2

#define LineWalk_L1_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_L2_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_R1_RCC    	RCC_APB2Periph_GPIOC
#define LineWalk_R2_RCC		RCC_APB2Periph_GPIOB

#define LineWalk_L1_PIN		GPIO_Pin_14
#define LineWalk_L2_PIN		GPIO_Pin_13
#define LineWalk_R1_PIN		GPIO_Pin_15
#define LineWalk_R2_PIN		GPIO_Pin_12

#define LineWalk_L1_PORT	GPIOC
#define LineWalk_L2_PORT	GPIOC
#define LineWalk_R1_PORT	GPIOC
#define LineWalk_R2_PORT	GPIOB

void Line_Walking_Gpio_Init(void);
void GetLineWalking(int *p_iL1, int *p_iL2, int *p_iR1, int *p_iR2);
void LineWalking(void);
#endif

