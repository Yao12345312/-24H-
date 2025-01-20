#ifndef __Motor_H
#define	__Motor_H

void Motor_Init(void);
void Left_Motor_Speed(int16_t Speed);
void Right_Motor_Speed(int16_t Speed);
void Motor_Limitation(int16_t* Left_Speed,int16_t* Right_Speed);
#endif

