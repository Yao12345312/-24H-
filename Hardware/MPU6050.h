#ifndef __MPU6050_H__
#define __MPU6050_H__

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);  //RegAddress为要写入的寄存器地址
uint8_t MPU6050_ReadReg(uint8_t RegAddress);   //指定地址读字节
void MPU6050_Init(void);
void  MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
						int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ); 

#endif

