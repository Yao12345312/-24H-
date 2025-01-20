#ifndef __MyI2C_H
#define __MyI2C_H

void MyI2C_W_SCL(uint8_t BitValue); //uint8_t相当于unsigned char,作用：写入寄存器
void MyI2C_W_SDA(uint8_t BitValue); 
uint8_t MyI2C_R_SDA(void); //读寄存器
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte); //一位一位发送
uint8_t MyI2C_ReceiveByte(void);  //接收数据
void MyI2C_SendAck(uint8_t AckBit); //发送应答
uint8_t MyI2C_ReceiveAck(void);     //接收应答

#endif




