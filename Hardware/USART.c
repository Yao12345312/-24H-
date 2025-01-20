#include "stm32f10x.h"                  // Device header
#include "stdio.h"   
/*
* Function   
* @date           
* @brief        配置蓝牙，串口初始化
* @param[in]   void
* @param[out]    void
* @retval    
* @par History   
*/
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置GPIO口
	GPIO_InitTypeDef GPIO_Initstructure;  //TXD(A2)
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP; 
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IPU; //RXD(A3)
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600; //配置波特率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用流控
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; //发送，接收模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//无校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//1位停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//8位字长
	
	USART_Init(USART1, &USART_InitStructure);
	//配置NVIC中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE); //开启中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;//选择通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//为什么是RESET
}

void Serial_Array(uint8_t *Array,uint16_t Lenth)
{
	for(int i=0;i<Lenth;i++)
	{
	Serial_SendByte(Array[i]);
	}
}

void Serial_String(uint8_t *String)
{
	 for(int i=0;String[i]!='\0';i++)
	{
	Serial_SendByte(String[i]);
	}
}
//换行操作 \r\n
