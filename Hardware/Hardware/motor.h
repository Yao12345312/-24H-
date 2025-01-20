#ifndef __Motor_H
#define	__Motor_H

void Motor_Init(void);
void Left_Motor_Speed(int16_t Speed);
void Right_Motor_Speed(int16_t Speed);
void Motor_Limitation(float* Left_Speed,float* Right_Speed);
#endif

