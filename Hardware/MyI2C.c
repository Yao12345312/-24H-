#include "stm32f10x.h"  
#include "Delay.h"  

void MyI2C_W_SCL(uint8_t BitValue) //uint8_t相当于unsigned char,作用：写入寄存器
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue) 
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void) //读寄存器
{
    uint8_t BitValue;
 	BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return BitValue;
}



void MyI2C_Init(void)	
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//配置GPIO口
	GPIO_InitTypeDef GPIO_Initstructure;  //初始化结构体
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_OD; //开漏输出
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); //I2C初始化，给SCL/SDA接高电平
	
	
}

void MyI2C_Start(void)
{
    MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
    MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte) //一位一位发送
{
	for(uint8_t i=0;i<8;i++)
	{
	MyI2C_W_SDA(Byte & (0x80>>i) ); //由高位到低位
	MyI2C_W_SCL(1);                 //模拟时序图
	MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)  //接收数据
{
	uint8_t Byte=0x00; //每次接受的位都不同，需要放到外面
	MyI2C_W_SDA(1);
	for(uint8_t i=0;i<8;i++)
	{
	MyI2C_W_SCL(1); 
	if(MyI2C_R_SDA()==1){Byte|=(0x80>>i);} //模拟时序
	MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit) //发送应答
{
	MyI2C_W_SDA(AckBit); 
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
}

uint8_t MyI2C_ReceiveAck(void)     //接收应答
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1); 
	AckBit=MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	
	return AckBit;
}
