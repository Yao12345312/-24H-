#include "stm32f10x.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS  0xD0

/*
* Function   
* @date           
* @brief        死循环等待超时退出
* @param[in]   I2Cx I2C_EVENT
* @param[out]    void
* @retval    
* @par History   
*/

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		Timeout --;
		if (Timeout == 0)
		{
			break;
		}
	}
}

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	
	I2C_SendData(I2C2, Data);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
	
	I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);
	
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	return Data;
}

void MPU6050_Init(void)
{	//配置GPIO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//配置I2C2
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed = 100000;     //0-400KHz 50000
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;     //作为从机的地址，暂时不需要 
	I2C_Init(I2C2, &I2C_InitStructure);
	
	I2C_Cmd(I2C2, ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
	
		MPU6050_WriteReg(MPU6050_INTBP_CFG_REG, 0x80);
		MPU6050_WriteReg(MPU6050_EN_REG, 0x01);
}

void  MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
						int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
	uint16_t Data_H,Data_L;
	
	Data_H=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);  //X轴加速度
	Data_L=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX=(Data_H << 8)|Data_L;
	
	Data_H=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);  //Y轴加速度
	Data_L=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY=(Data_H << 8)|Data_L;
	
	Data_H=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);  //Z轴加速度
	Data_L=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ=(Data_H << 8)|Data_L;
	
	Data_H=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);  //X轴角速度
	Data_L=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX=(Data_H << 8)|Data_L;
	
	Data_H=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	Data_L=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	*GyroY=(Data_H << 8)|Data_L; 
	
	Data_H=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	Data_L=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	*GyroZ=(Data_H << 8)|Data_L;
	
}
